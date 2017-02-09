#ifndef P_CLIENT_H
#define P_CLIENT_H

#include "p_json_tcp.h"

#include <QObject>
#include <QQmlEngine>
#include <QJSEngine>



class PClient : public QObject
{
    Q_OBJECT
public:
    explicit PClient(QObject *parent = nullptr);

    Q_PROPERTY(bool loggedIn READ loggedIn NOTIFY userChanged)
    Q_PROPERTY(QVariantMap user READ user NOTIFY userChanged)
    Q_PROPERTY(int playCt READ playCt NOTIFY userChanged)
    Q_PROPERTY(int connCt READ connCt NOTIFY lookedAround)
    Q_PROPERTY(QVariantMap books READ books NOTIFY lookedAround)
    Q_PROPERTY(int lastNonce READ lastNonce NOTIFY lastNonceChanged)

    Q_INVOKABLE void login(const QString &username, const QString &password);
    Q_INVOKABLE void signUp(const QString &username, const QString &password);
    Q_INVOKABLE void lookAround();
    Q_INVOKABLE void book(const QString &bookType);
    Q_INVOKABLE void unbook();
    Q_INVOKABLE void sendReady();

    QVariantMap user() const;
    bool loggedIn() const;
    int playCt() const;
    int connCt() const;
    QVariantMap books() const;
    int lastNonce() const;


signals:
    void remoteClosed();
    void connError();
    void authFailIn(const QString &reason);
    void startIn(const QVariantList &users, const QVariantList &girlIds, int tempDealer);

    void userChanged();
    void lookedAround();
    void lastNonceChanged();

    void firstDealerChoosen(int dealer);
    void roundStarted(int round, int extra, int dealer, bool allLast, int deposit);
    void cleaned();
    void diced(int die1, int die2);
    void dealt(const QVariant &init);
    void flipped(const QVariant &newIndic);
    void drawn(int who, const QVariant &tile, bool rinshan);
    void discarded(int who, const QVariant &tile, bool spin);
    void riichiCalled(int who);
    void riichiEstablished(int who);
    void barked(int who, int fromWhom, QString actStr, const QVariant &bark, bool spin);
    void roundEnded(QString result, const QVariant &openers, int gunner,
                    const QVariant &hands, const QVariant &forms, const QVariant &urids);
    void pointsChanged(const QVariant &points);
    void tableEnded(const QVariant &rank, const QVariant &scores);
    void poppedUp(QString str);
    void activated(const QVariant &action, int lastDiscarder, bool green, int nonce);
    void deactivated();

public slots:
    void action(QString actStr, const QVariant &actArg);

private:
    void onRemoteClosed();
    void send(const QJsonObject &obj);
    void onJsonReceived(const QJsonObject &msg);
    void recvTableEvent(const QString &type, const QJsonObject &msg);

    QString hash(const QString &password) const;

private:
    PJsonTcpSocket mSocket;
    QVariantMap mUser;
    int mConnCt = 0;
    QVariantMap mBooks;
    int mLastNonce = 0;
};

QObject *pClientSingletonProvider(QQmlEngine *engine, QJSEngine *scriptEngine);



#endif // P_CLIENT_H


