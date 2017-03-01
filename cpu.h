#ifndef CPU_H
#define CPU_H
#include "baseplayer.h"
#include "cpumind.h"

class Cpu : public BasePlayer
{
public:
    Cpu();
    ~Cpu();
    void appendCard(Card *);
    void appendCard(Card *c, int n);
    CpuMind & getCpuMind();
    const CpuMind &getCpuMind() const;
    using BasePlayer::setBlefChoice;
    void setBlefChoice(int blefMainNr, QString blefMainString, int blefValueNr, QString blefValueString);
private:
    CpuMind *mind;
};

#endif // CPU_H
