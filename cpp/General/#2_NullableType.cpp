#include <stdlib.h>
#include <stdio.h>
#include <exception>

// Just for print in console ( std::cout / std::endl )
//safe to remove as long you remove the print function
#include <iostream>


template<typename T>
class Nullable
{
public:
    constexpr bool IsNull() const { return m_isNull; }

    Nullable()
    {
        m_buff = 0;
        m_isNull = true;
    }

    Nullable(T t)
    {
        m_buff = (T*)malloc(sizeof(T));
        *m_buff = t;
        m_isNull = false;
    }

    template<typename...TArgs>
    Nullable(TArgs...args)
    {
        static_assert(std::is_constructible_v<T, TArgs...>, "Uconstructable Nullable");
        m_buff = (T*)malloc(sizeof(T));
        *m_buff = T(args...);
        m_isNull = false;
    }

    bool Nullify()
    {
	    if (m_isNull)  return false;
        free(m_buff);
        return m_isNull = true;
    }

	explicit operator T()
	{
        if (m_isNull)
            throw std::exception("(Nullable<T> Object).m_data is null.");
        return *m_buff;
	}

	Nullable<T>& operator=(const T& obj)
    {
	    if(m_isNull)
	    {
            m_buff = (T*)malloc(sizeof(T));
            m_isNull = false;
	    }
        *m_buff = obj;
        return *this;
    }

	// The following code requires iostream header, safe to remove
    void Print()
    {
        try
        {
            std::cout << (T)*this << "\n";
        }
        catch (std::exception& ex)
        {
            std::cout << ex.what() << "\n";
        }
    }
private:
    bool m_isNull;
    T* m_buff;
};

// Just an exemple
int main()
{
    Nullable<int> i = 5;

    i.Print();
    i.Nullify();
    i.Print();
    i = 9;
    i.Print();
    
    system("pause");
    return 0;
}
