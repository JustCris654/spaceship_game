#ifndef AIRCRAFT_H_
#define AIRCRAFT_H_

#include "../BaseEntity.hpp"

class Aircraft : public BaseEntity {
  public:
    enum Type {
      Eagle,
      Raptor,
    };

  public:
    explicit Aircraft(Type type);

  private:
    Type m_Type;
};

#endif // AIRCRAFT_H_
