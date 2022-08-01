#ifndef LWMODELSQLQUERY_H
#define LWMODELSQLQUERY_H

#include <QObject>
#include <QtCore>
#include <QtQml>
#include <QAbstractItemModel>

class LWModelSQLQuery : public QAbstractTableModel
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(QJsonObject modelData READ modelData WRITE setModelData NOTIFY modelDataChanged)

public:
    explicit LWModelSQLQuery(QObject *parent = nullptr);


    int rowCount(const QModelIndex& index = QModelIndex()) const override;
    int columnCount(const QModelIndex& index = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE QJsonObject modelData() const;
    Q_INVOKABLE void setModelData(const QJsonObject& modelData);

signals:
    void modelDataChanged();

protected:
    QJsonObject _modelData;
};

#endif // LWMODELSQLQUERY_H
