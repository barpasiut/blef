#ifndef CARD_H
#define CARD_H
#include <QGraphicsPixmapItem>

class Card : public QGraphicsPixmapItem
{
public:
    static const int numberOfCardsInDeck = 24;
    Card();
    ~Card();
    int getNumber() const;
    int getWidth() const;
    int getHeight() const;
    const QString & getColor() const;
    const QString & getPath() const;
    const QString & getNumberAndColor() const;
    void setNumber(int);
    void setWidth(int);
    void setHeight(int);
    void setColor(const QString &);
    void setPath(const QString &);
    void setNumberAndColor(const QString &);
    void setScaleCard(qreal);
    void setUnUsedCards();
    void setUnUsedCards(QList<QString>);
    static QList<QString> & getUnUsedCards();
    static const int getNumberOfCardsInDeck();
    void setPixmapCard(const QPixmap &);
protected:
    void randCard(const QString &);
private:
    static QList<QString> unUsedCards;
    int number;
    int width;
    int height;
    QString color;
    QString path;
    QString numberAndColor;
};

QList<QString> cardsList();

#endif // CARD_H
