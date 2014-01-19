#ifndef USEROBJECT_H
#define USEROBJECT_H

#include <vector>
#include <string>
#include <stdarg.h>
#include <cassert>
#include <typeinfo>
using namespace std;

#ifndef SVECTOR_H
    #include "SVector.h"
#endif
#ifndef SERIALIZABLE_H
    #include "ISerializable.h"
#endif

namespace Serialization
{
    class UserObject : public ISerializable
    {
        enum ObjectState
        {
            Initialized     = 0xf0f0f0f0,
            Uninitialized   = 0x0f0f0f0f
        };

    private:
        ObjectState     _objectState;
        SVector<char*>   _membersaddresses;

    protected:
        void AddMemberAddress(unsigned nAddresses, ...)
        {
            void* memberAddress;
            va_list argList;
            // The va_start macro is usually equivalent to:
            // pArgList = (void*) &p_memberAddress + sizeof (p_memberAddress) ;
            va_start (argList, nAddresses);
            ++nAddresses;
            while(--nAddresses)
            {
                memberAddress = va_arg(argList, void*);
                _membersaddresses.push_back(reinterpret_cast<char*>(memberAddress));
            }
            va_end (argList) ;
        }

        virtual void    InitializeAddressesAux() = 0;

    public:
                        UserObject() : _objectState(Uninitialized) {}
        Iterator*       GetIterator()   { return new VectorIterator<char*>(&_membersaddresses); }

        void InitializeAddresses()
        {
            // catch any type-casting failure by assuring a predefinded values
            assert(_objectState == Initialized || _objectState == Uninitialized);
            if(_objectState == Uninitialized) 
            {
                InitializeAddressesAux();
                _objectState = Initialized;
            }
        }
    };
}
#endif // USEROBJECT_H
