// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

// Fake variables used as placeholders in tests
static const int FAKE_INT = -1;
static TBitField FAKE_BITFIELD(1);
//добавить исключения на BitLen

TBitField::TBitField(int len)
{
	BitLen = len;
	MemLen = BitLen / sizeof(TELEM) * 8 + 1;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
	{
		pMem[i] = 0;
	}
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
	{
		pMem[i] = bf.pMem[i];
	}
}

TBitField::~TBitField()
{
	delete[] pMem;
	BitLen = 0;
	MemLen = 0;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	return (n / (sizeof(TELEM) * 8));
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	TELEM res = 1;
	int ind = n % (sizeof(TELEM) * 8);
	res <<= ind;
	return res;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return FAKE_INT;
}

void TBitField::SetBit(const int n) // установить бит
{
	pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
	pMem[GetMemIndex(n)] &= (!GetMemMask(n));
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	TELEM& a = pMem[GetMemIndex(n)];
	TELEM b = GetMemMask(n);
	TELEM Res = a & b;
	if (Res)
		return 1;
	return 0;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
    return FAKE_BITFIELD;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
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

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	return !(*this == bf);
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int maxlen = std::min(BitLen, bf.BitLen);
	TBitField res(maxlen);
	//...
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    return FAKE_BITFIELD;
}

TBitField TBitField::operator~(void) // отрицание
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
//	 TBitField TBitField::operator~(void)
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





// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	char temp;
	istr >> temp;
	for (int i = 0; temp == '0' || temp == '1'; i++) {
		istr >> temp;
		if (temp == '0')
			bf.ClrBit(i);
		else if (temp == '1')
			bf.SetBit(i);
		else
			return istr;

	}
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	for (int i = 0; i < bf.BitLen; i++)
	{
		ostr << bf.GetBit(i);
	}
	return ostr;
}
