#include <iostream>

using namespace std;

const size_t MAX_VECTOR_SIZE = 100000000;
const size_t MAX_MATRIX_SIZE = 10000;

template<typename T>
class TDynamicVector
{
protected:
  size_t sz;
  T* pMem;
public:

  TDynamicVector(size_t size = 1) : sz(size)
  {
      if (sz == 0) {
          throw out_of_range("Vector size should be greater than zero");
      }
      if (sz > MAX_VECTOR_SIZE) {
          throw out_of_range("Error");
      }
      pMem = new T[sz]();
  }

  TDynamicVector(T* arr, size_t s) : sz(s)
  {
    pMem = new T[sz];
    std::copy(arr, arr + sz, pMem);
  }

  TDynamicVector(const TDynamicVector& v) : TDynamicVector(v.pMem, v.sz) {}

  TDynamicVector(TDynamicVector&& v) noexcept
  {
      pMem = v.pMem;
      v.pMem = nullptr;
      sz = v.sz;
  }

  ~TDynamicVector()
  {
      delete[] pMem;
  }

  TDynamicVector& operator=(const TDynamicVector& v)
  {
      if (this != &v)
          *this = TDynamicVector(v);
      return *this;
  }
  TDynamicVector& operator=(TDynamicVector&& v) noexcept
  {
      swap(pMem, v.pMem);
      sz = v.sz;
      return *this;
  }

  size_t size() const noexcept
  { 
      return sz; 
  }

  T& operator[](size_t ind)
  {
      if (ind >= sz || ind < 0) 
          throw out_of_range("Error");
      return pMem[ind];
  }

  const T& operator[](size_t ind) const
  {
      if (ind >= sz || ind < 0) 
          throw out_of_range("Error");
      return pMem[ind];
  }

  T& at(size_t ind)
  {
      if (ind >= sz) {
          throw out_of_range("Error");
      }
      return pMem[ind];
  }

  const T& at(size_t ind) const
  {
      if (ind >= sz) {
          throw out_of_range("Error");
      }
      return pMem[ind];
  }

  bool operator==(const TDynamicVector& v) const noexcept
  {
      if (this == &v)
          return true;
      if (sz != v.sz)
          return false;
      for (size_t i = 0; i < sz; i++)
          if (pMem[i] != v.pMem[i])
              return false;
      return true;
  }

  bool operator!=(const TDynamicVector& v) const noexcept
  {
      return !(*this == v);
  }

  TDynamicVector operator+(T val)
  {
      TDynamicVector result(this->sz);
      for (size_t i = 0; i < sz; i++) {
          result[i] = pMem[i] + val;
      }
      return result;
  }

  TDynamicVector operator-(T val)
  {
      TDynamicVector result(this->sz);
      for (size_t i = 0; i < sz; i++) {
          result[i] = pMem[i] - val;
      }
      return result;
  }

  TDynamicVector operator*(T val)
  {
      TDynamicVector result(this->sz);
      for (size_t i = 0; i < sz; i++) {
          result[i] = pMem[i] * val;
      }
      return result;
  }

  TDynamicVector operator+(const TDynamicVector& v)
  {
      if (sz != v.sz)
          throw logic_error("Error");
      TDynamicVector result(this->sz);
      for (size_t i = 0; i < sz; i++)
          result.pMem[i] = pMem[i] + v.pMem[i];
      return result;
  }

  TDynamicVector operator-(const TDynamicVector& v)
  {
      if (sz != v.sz)
          throw logic_error("Error");
      TDynamicVector result(this->sz);
      for (size_t i = 0; i < sz; i++)
          result.pMem[i] = pMem[i] - v.pMem[i];
      return result;
  }

  T operator*(const TDynamicVector& v) noexcept(noexcept(T()))
  {
      if (sz != v.sz)
          throw logic_error("Error");
      T result = pMem[0] * v.pMem[0];
      for (size_t i = 1; i < sz; i++) {
          result = result + pMem[i] * v.pMem[i];
      }
      return result;
  }

  friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
  {
    std::swap(lhs.sz, rhs.sz);
    std::swap(lhs.pMem, rhs.pMem);
  }

  friend istream& operator>>(istream& istr, TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      istr >> v.pMem[i];
    return istr;
  }

  friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      ostr << v.pMem[i] << ' ';
    return ostr;
  }
};

template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
  using TDynamicVector<TDynamicVector<T>>::pMem;
  using TDynamicVector<TDynamicVector<T>>::sz;
public:

  TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
  {
      if (s <= 0)
          throw out_of_range("Error");
      if (sz > MAX_MATRIX_SIZE)  
          throw out_of_range("Error");
      for (size_t i = 0; i < sz; i++)
          pMem[i] = TDynamicVector<T>(sz);
  }

  using TDynamicVector<TDynamicVector<T>>::operator[];

  bool operator==(const TDynamicMatrix& m) const noexcept
  {
      for (size_t i = 0; i < sz; i++) {
          if ((*this)[i] != m[i])
              return false;
      }
      return true;
  }

  TDynamicVector<T> operator*(const T& val)
  {
      if (sz != m.sz)
          throw "Error";
      TDynamicMatrix res(sz);
      for (size_t i = 0; i < sz; i++)
          res[i] = (*this)[i] * val;
      return res;
  }

  TDynamicVector<T> operator*(const TDynamicVector<T>& v)
  {
      if (sz != v.sz)
          throw logic_error("Error");
      TDynamicVector res(sz);
      for (size_t i = 0; i < sz; i++) {
          res[i] = (*this)[i] * v;
      }
      return res;
  }

  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
      TDynamicMatrix res(sz);
      for (size_t i = 0; i < sz; i++)
          res[i] = (*this)[i] + m[i];
      return res;
  }

  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
      TDynamicMatrix res(sz);
      for (size_t i = 0; i < sz; i++)
          res[i] = (*this)[i] - m[i];
      return res;
  }

  TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
      TDynamicMatrix res(sz);
      for (size_t i = 0; i < sz; i++)
          res[i] = (*this)[i] * m[i];
      return res;
  }

  size_t size() const noexcept
  {
      return sz;
  }

  friend istream& operator>>(istream& istr, TDynamicMatrix& v)
  {
      for (size_t i = 0; i < v.size(); i++) {
          for (size_t j = 0; j < v.size(); j++) {
              istr >> v[i][j];
          }
      }
      return istr;
  }

  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
  {
      for (size_t i = 0; i < v.size(); i++) {
          for (size_t j = 0; j < v.size(); j++) {
              ostr << v[i][j] << ' ';
          }
          ostr << endl;
      }
      return ostr;
  }
};