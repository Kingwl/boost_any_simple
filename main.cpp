#include <iostream>
#include <typeinfo>
class any{
public:
    void *_elemt;
    const std::type_info *_type_i;

    any():_type_i(nullptr),_elemt(nullptr){
    };

    any(const any& other)
    :_type_i(nullptr),_elemt(nullptr)
    {
        _type_i = other._type_i;
        _elemt = other._elemt;
    };

    any& operator= (const any& other)
    {
        void* tmp = _elemt;
        _type_i = other._type_i;
        _elemt = other._elemt;
        delete tmp;
    };

    template<class TypeValue>
    any(const TypeValue& o)
    {
        void* tmp = _elemt;
        _elemt = static_cast<void*>(new TypeValue(o));
        _type_i =  &typeid(o);
        delete tmp;
    };

    template<class TypeValue>
    any& operator= (const TypeValue& o)
    {
        void* tmp = _elemt;
        _elemt = static_cast<void*>(new TypeValue(o));
        _type_i =  std::move(&typeid(o));
        delete tmp;
    };
    virtual ~any(){
        delete _elemt;
        _elemt = nullptr;
        _type_i = nullptr;
    }
};

template<class TypeValue>
TypeValue* any_cast(const any &o)
{
    if(*(o._type_i) == typeid(TypeValue))
        return static_cast<TypeValue*>(o._elemt);
    return nullptr;
}

template<class TypeValue>
const TypeValue* any_cast_const(const any &o)
{
    if(*(o._type_i) == typeid(TypeValue))
        return static_cast<const TypeValue*>(o._elemt);
    return nullptr;
}

int main()
{
    any a(123);
    int* t = any_cast<int>(a);
    std::cout << *t << std::endl;
    a = std::string("22");
    std::string *s = any_cast<std::string>(a);
    std::cout << *s << std::endl;
    return 0;
}
