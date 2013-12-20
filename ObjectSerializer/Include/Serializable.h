#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#ifndef TRAVERSABLE_H
	#include "Traversable.h"
#endif
#include <typeinfo>

namespace Serialization
{
    class Serializable : public Traversable
    {
    public:
        virtual std::string     TypeName()  = 0;
        virtual int             TypeSize()  = 0;
        virtual Serializable*   Prototype() = 0;
        std::string             CName() { return typeid(*this).name(); }
    };
}

#define OBJECT_SERIALIZABLE(ClassName) \
	public: \
	std::string					TypeName()  { return #ClassName; } \
	int							TypeSize()  { return sizeof(ClassName); } \
	Serialization::UserObject*	Prototype() { return new ClassName; }	

#endif // SERIALIZABLE_H
