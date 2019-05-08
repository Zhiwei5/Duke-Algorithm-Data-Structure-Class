/* -*- C++ -*- */

#include <iostream>
#include <sstream>
#include <string>

class Expression
{
 protected:
  std::stringstream ss;

 public:
  Expression() : ss() {}
  virtual std::string toString() const = 0;
  virtual ~Expression() {}
};

class NumExpression : public Expression
{
 protected:
  long number;

 public:
  NumExpression(long input_number) : number(input_number) { ss << number; }
  virtual std::string toString() const { return ss.str(); }

  virtual ~NumExpression() {}
};

class OPExpression : public Expression
{
 public:
  virtual std::string toString() const { return ss.str(); }
  virtual ~OPExpression() {}
};

class PlusExpression : public OPExpression
{
 public:
  PlusExpression(Expression * lhs, Expression * rhs) {
    ss << "(" << lhs->toString() << " + " << rhs->toString() << ")";
    delete lhs;
    delete rhs;
  }
  virtual ~PlusExpression() {}
};

class MinusExpression : public OPExpression
{
 public:
  MinusExpression(Expression * lhs, Expression * rhs) {
    ss << "(" << lhs->toString() << " - " << rhs->toString() << ")";
    delete lhs;
    delete rhs;
  }
  virtual ~MinusExpression() {}
};

class TimesExpression : public OPExpression
{
 public:
  TimesExpression(Expression * lhs, Expression * rhs) {
    ss << "(" << lhs->toString() << " * " << rhs->toString() << ")";
    delete lhs;
    delete rhs;
  }
  virtual ~TimesExpression() {}
};

class DivExpression : public OPExpression
{
 public:
  DivExpression(Expression * lhs, Expression * rhs) {
    ss << "(" << lhs->toString() << " / " << rhs->toString() << ")";
    delete lhs;
    delete rhs;
  }
  virtual ~DivExpression() {}
};
