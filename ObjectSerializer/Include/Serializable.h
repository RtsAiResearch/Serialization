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
        virtual std::string     TypeName()  const = 0;
        virtual int             TypeSize()  const = 0;
        virtual Serializable*   Prototype() const = 0;
        std::string             CName() const { return typeid(*this).name(); }
    };
}

#define OBJECT_SERIALIZABLE(ClassName) \
	public: \
	std::string					TypeName()  const { return #ClassName; } \
	int							TypeSize()  const { return sizeof(ClassName); } \
	Serialization::UserObject*	Prototype() const { return new ClassName; }	

#endif // SERIALIZABLE_H
