#include "LWModelSQLQuery.h"

LWModelSQLQuery::LWModelSQLQuery(QObject *parent)
    : QAbstractTableModel{parent}
{

}

int LWModelSQLQuery::rowCount(const QModelIndex &index) const
{
    qDebug() << _modelData["rows"].toArray().count();
    return _modelData["rows"].toArray().count();
}

int LWModelSQLQuery::columnCount(const QModelIndex &index) const
{
    return _modelData["fields"].toArray().count();
}

QVariant LWModelSQLQuery::data(const QModelIndex &index, int role) const
{
    switch (role) {
    case Qt::DisplayRole:
        qDebug() << 'a';
        return QString("%1, %2").arg(index.column()).arg(index.row());
    default:
        break;
    }
    return QVariant();
}

QHash<int, QByteArray> LWModelSQLQuery::roleNames() const
{
    return {{Qt::DisplayRole, "display"}};
}

QJsonObject LWModelSQLQuery::modelData() const
{
    return _modelData;
}

void LWModelSQLQuery::setModelData(const QJsonObject &modelData)
{
    _modelData = modelData;
    qDebug() << rowCount()-1 << "," << columnCount()-1;
    beginResetModel();
    emit dataChanged(index(0,0), index(rowCount()-1,columnCount()-1));
    endResetModel();
}
