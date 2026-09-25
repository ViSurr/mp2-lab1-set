#ifndef clASSSSS
#define clASSSSS

#include <iostream>
#include "funcs.h"

typedef unsigned int TELEM;


class TBitField
{
   //добавить исключения на BitLen
   int BitLen, MemLen;
   TELEM* pMem;
   int GetMemIndex(const int i) const
   {
      return (i / (sizeof(TELEM) * 8));
   }
   TELEM GetMemMask(const int i) const
   {
      TELEM res = 1;
      int ind = i % (sizeof(TELEM) * 8);
      res <<= ind;
      return res;
   }

public:

   TBitField(int _BitLen)
   {
      BitLen = _BitLen;
      MemLen = BitLen / sizeof(TELEM) * 8 + 1;
      pMem = new TELEM[MemLen];
      for (int i = 0; i < MemLen; i++)
      {
         pMem[i] = 0;
      }
   }

   TBitField(const TBitField& a)
   {
      BitLen = a.BitLen;
      MemLen = a.MemLen;
      pMem = new TELEM[MemLen];
      for (int i = 0; i < MemLen; i++)
      {
         pMem[i] = a.pMem[i];
      }
   }
   ~TBitField()
   {
      delete[] pMem;
      BitLen = 0;
      MemLen = 0;
   }


   void SetBit(int i)
   {
      pMem[GetMemIndex(i)] |= GetMemMask(i);
   }
   void ClrBit(int i)
   {
      pMem[GetMemIndex(i)] &= (!GetMemMask(i));
   }
   int GetBit(int i) const
   {
      TELEM& a = pMem[GetMemIndex(i)];
      TELEM b = GetMemMask(i);
      TELEM Res = a & b;
      if (Res)
         return 1;
      return 0;
   }

   bool operator==(const TBitField& bf) const
   {
      if (BitLen != bf.BitLen)
         return false;
      for (int i = 0; i < MemLen - 1; i++)
      {
         if (pMem[i] != bf.pMem[i])
            return false;
      }
      for (int i = (pMem[i] - 1) * sizeof(TELEM) * 8; i < BitLen; i++)
      {
         if (GetBit(i) != bf.GetBit(i))
            return false;
      }
      return true;
   }

   bool operator!=(const TBitField& bf) const
   {
      return !(*this == bf);
   }

   //TBitField operator~() const
 //  {
 //   TBitField res =*this;
 //   for(int i=0; i<BitLen;i++)
 //   {
 //    if(res.GetBit(i)==1)
 //    res.ClrBit(i);
 //    else
 //    res.SetBit(i); 
 //   }
 //   return res;
 //  }

   TBitField operator~() const
   {
      TBitField res = *this;
      for (int i = 0; i < MemLen - 1; i++)
      {
         res.pMem[i] = ~pMem[i];
      }
      for (int i = (pMem[i] - 1) * sizeof(TELEM) * 8; i < BitLen; i++)
      {
         if (res.GetBit(i) == 1)
            res.ClrBit(i);
         else
            res.SetBit(i);
      }
      return res;
   }

   TBitField operator|(const TBitField& bf) const
   {
      int maxlen = std::min(BitLen, bf.BitLen);
      TBitField res(maxlen);
      //...
   }
   TBitField operator&(const TBitField& bf) const {}

   // решётка Эратосфена

   friend std::ostream& operator<<(std::ostream& os, const TBitField bf);
   friend std::istream& operator>>(std::istream& is, TBitField& bf);
};

std::ostream& operator<<(std::ostream& os, const TBitField bf)
{
   for (int i = 0; i < bf.BitLen; i++)
   {
      os << bf.GetBit(i);
   }
   return os;
}
std::istream& operator>>(std::istream& is, TBitField& bf)
{
   char temp;
   is >> temp;
   for (int i = 0; temp == '0' || temp == '1'; i++) {
      is >> temp;
      if (temp == '0')
         bf.ClrBit(i);
      else if (temp == '1')
         bf.SetBit(i);
      else
         return is;

   }
}







template <typename T>
class Container {
   int size;
   T* pMem;
public:
   Container(int s = 10)
   {
      if (s <= 0)
         throw std::out_of_range("Memory can't be zero or less ");
      size = s;
      pMem = new T[size];

   }

   Container(const Container<T>& cont)
   {
      size = cont.size;
      pMem = new T[size];
      for (int i = 0; i < size; i++)
      {
         pMem[i] = cont.pMem[i];
      }
   }

   Container(Container&& cont)
   {
      size = cont.size;
      pMem = cont.pMem;
      cont.size = 0;
      cont.pMem = nullptr;
   }


   ~Container()
   {
      if (pMem)
         delete[] pMem;
   }

   int getsize() const
   {
      return size;
   }

   int find(T a)
   {
      for (int i = 0; i < size; i++)
      {
         if (a == pMem[i])
            return i;
      }
      return -1;
   }

   void print()
   {
      for (int i = 0; i < size; i++)
      {
         std::cout << pMem[i] << " ";
      }
      std::cout << std::endl;
   }

   void resize(int i)
   {
      if (i == size)
         return;
      T* temp = new T[i];
      for (int ind = 0, j = min(size, i); ind < j; ind++)
      {
         temp[ind] = pMem[ind];
      }
      delete[]pMem;
      pMem = temp;
      temp = nullptr;
      size = i;
   }

   void add(const T& a)
   {
      resize(size + 1);
      pMem[size - 1] = a;
   }

   T pop()
   {
      T temp = pMem[size - 1];
      resize(--size);

      return temp;
   }

   void insert(int ind, T a)
   {
      T* temp = new T[++size];
      for (int i = 0; i < ind; i++)
      {
         temp[i] = pMem[i];
      }
      temp[ind] = a;
      for (int i = ind + 1; i < size; i++)
      {
         temp[i] = pMem[i - 1];
      }
      delete[] pMem;
      pMem = temp;
      temp = nullptr;
   }

   void erase(int ind)
   {
      T* temp = new T[--size];
      for (int i = 0; i < ind; i++)
      {
         temp[i] = pMem[i];
      }

      for (int i = ind; i < size; i++)
      {
         temp[i] = pMem[i + 1];
      }
      delete[] pMem;
      pMem = temp;
      temp = nullptr;
   }

   void remove(T a)
   {
      int ind = find(a);
      if (ind == -1) return;
      erase(ind);
   }

   Container<T>& operator=(const Container<T>& cont)
   {
      if (this != &cont)
      {
         if (size != cont.size)
         {
            size = cont.size;
            delete[] pMem;
            pMem = new T[size];
         }
         for (int i = 0; i < size; i++)
         {
            pMem[i] = cont.pMem[i];
         }
      }
      return *this;
   }


   Container<T>& operator=(Container&& cont)
   {
      if (this != &cont) {
         size = cont.size;
         delete[] pMem;
         pMem = cont.pMem;
         cont.pMem = nullptr;
         cont.size = 0;
      }
      return *this;
   }

   T& operator[](int i)
   {
      return pMem[i];
   }
   const T& operator[](int i) const
   {
      return pMem[i];
   }

   bool operator==(const Container<T>& cont) const
   {
      if (this == &cont) return 1;
      if (size != cont.size) return 0;
      for (int i = 0; i < size; i++)
      {
         if (pMem[i] != cont.pMem[i])return 0;
      }
      return 1;
   }

   bool operator!=(const Container<T>& cont) const
   {
      return !(*this == cont);
   }

   Container<T> operator+ (const Container<T> cont) const
   {
      Container<T> res(size + cont.size);
      for (int i = 0; i < size; i++)
      {
         res.pMem[i] = pMem[i];
      }
      for (int i = 0; i < cont.size; i++)
      {
         res.pMem[size + i] = cont.pMem[i];
      }
      return res;
   }
   Container<T> operator- (const Container<T> cont) const
   {
      Container<T> res(*this);
      for (int i = 0; i < cont.size; i++)
      {
         res.remove(cont.pMem[i]);
      }
      return res;
   }

};


#endif // !clASSSSS