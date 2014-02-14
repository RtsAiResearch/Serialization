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

    
    public:
                        UserObject() : m_objectState(Uninitialized) {}
        Iterator*       GetIterator()   { return new VectorIterator<char*>(&m_membersAddresses); }

        void InitializeAddresses()
        {
            // catch any type-casting failure by assuring a predefinded values
            _ASSERTE(Initialized == m_objectState || Uninitialized == m_objectState);
            if(Uninitialized == m_objectState ) 
            {
                InitializeAddressesAux();
                m_objectState = Initialized;
            }
        }

    private:
        ObjectState     m_objectState;
        SVector<char*>   m_membersAddresses;

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
                m_membersAddresses.push_back(reinterpret_cast<char*>(memberAddress));
            }
            va_end (argList) ;
        }

        virtual void    InitializeAddressesAux() = 0;
    };

#define OBJECT_MEMBERS(N, ...) \
    protected: \
        void InitializeAddressesAux() { AddMemberAddress(N, __VA_ARGS__); }

}
#endif // USEROBJECT_H
