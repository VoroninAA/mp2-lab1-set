// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	if (len < 0)
		throw std::runtime_error("len is less than 0");
	BitLen = len;
	MemLen = (len-1)/32+1;
	pMem= new TELEM[len]();
	
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen]();
	for (size_t i = 0; i <MemLen; i++)

	{
		pMem[i] = bf.pMem[i];
	}
}

TBitField::~TBitField()
{
	delete[] pMem;
	pMem = NULL;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if (n < 0)
		throw std::runtime_error("n is less than 0");
	return n/32;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	if (n < 0)
		throw std::runtime_error("n is less than 0");
	TELEM Mask;
	Mask = (1 << (n % 32));
	return Mask;
	
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if (n < 0 || n>BitLen)
		throw std::runtime_error("n is wrong");
	pMem[GetMemIndex(n)] |= GetMemMask(n);
	return;
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if (n < 0 || n>BitLen)
		throw std::runtime_error("n is wrong");
	pMem[GetMemIndex(n)] &= ~GetMemMask(n);
	return;
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if (n < 0 || n>BitLen)
		throw std::runtime_error("n is wrong");
  return pMem[GetMemIndex(n)]&GetMemMask(n);
	return 1;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (this == &bf)
		return *this;
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	delete[] pMem;
	pMem = new TELEM[MemLen];
	for (size_t i = 0; i < MemLen; i++)
	{
		pMem[i] = bf.pMem[i];
	}
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	if (BitLen == bf.BitLen)
		for (size_t i = 0; i <MemLen; i++)
		{
			if (pMem[i] != bf.pMem[i])
				return 0;
		}
	else return 0;
  return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{

	if (BitLen == bf.BitLen)
		for (size_t i = 0; i < MemLen; i++)
		{
			if (pMem[i] != bf.pMem[i])
				return 1;
		}
	else return 1;
	return 0;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	TBitField tmp(bf);
	int size = bf.MemLen;
	if (BitLen > bf.BitLen) 
	{
		TBitField tmp(*this);
		size = MemLen;
	}

	for (size_t i = 0; i < size; i++)
	{
		tmp.pMem[i] = pMem[i] | bf.pMem[i];
	}
	return tmp;

}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	if (BitLen > bf.BitLen) {
		TBitField tmp(BitLen);
		for (size_t i = 0; i < MemLen; i++)
		{
			tmp.pMem[i] = pMem[i] & bf.pMem[i];
		}
		return tmp;
	}
	else
	{
		TBitField tmp(bf.BitLen);
		for (size_t i = 0; i < bf.MemLen; i++)
		{
			tmp.pMem[i] = pMem[i] & bf.pMem[i];
		}
		return tmp;
	}
	
}



TBitField TBitField::operator~(void) // отрицание
{
	TBitField tmp(BitLen);
	for (size_t i = 0; i < BitLen; i++)
	{
		if (!GetBit(i))
			tmp.SetBit(i);
		else
			tmp.ClrBit(i);
		
		//tmp.pMem[i] = ~pMem[i];
	}
	return tmp;

}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	int tmp;
	for (size_t i = 0; i < bf.BitLen; i++)
	{
		istr >> tmp;
		bf.SetBit(tmp);
	}
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	for (size_t i = 0; i < bf.BitLen; i++)
	{
		if (bf.GetBit(i))
			ostr << 1;
		else ostr << 0;
	}
	return ostr;
}
