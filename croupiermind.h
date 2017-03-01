#ifndef CROUPIERMIND_H
#define CROUPIERMIND_H
#include "mind.h"

class CroupierMind : public Mind
{
public:
    CroupierMind();
    ~CroupierMind();
    void initializeHelpAttributes(const QString &blef, const QList<QString> &allUsedCards);
    bool isPlayerCheckWin(const QString &blef, const QList<QString> &allUsedCards);
    bool isAllCardsLayoutPriEqualToBlefPri();
};

#endif // CROUPIERMIND_H
