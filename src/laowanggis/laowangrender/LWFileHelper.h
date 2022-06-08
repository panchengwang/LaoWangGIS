#ifndef LWFILEHELPER_H
#define LWFILEHELPER_H

#include <string>


class LWFileHelper
{
public:
    LWFileHelper();

    std::string randomFileName();
    std::string tempFileName();
    std::string tempFilePath();
};

#endif // LWFILEHELPER_H
