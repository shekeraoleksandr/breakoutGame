#include <QtTest>
#include "../include/breakout.h"

//TEST(BreakoutTest, GameStarted)
//{
//    Breakout breakout;
//    ASSERT_TRUE(breakout.isGameStarted());
//}
//
//TEST(BreakoutTest, GamePaused)
//{
//    Breakout breakout;
//    ASSERT_TRUE(breakout.isGamePaused());
//}
//
//TEST(BreakoutTest, GameStopped)
//{
//    Breakout breakout;
//    ASSERT_TRUE(breakout.isGameStopped());
//}
//
//TEST(BreakoutTest, GameWon)
//{
//    Breakout breakout;
//    ASSERT_TRUE(breakout.isGameWon());
//}

//TEST(TRY_TEST, TEST){
//    int val = true;
//    ASSERT_TRUE(val);
//}


class TestBreakout : public QObject {
    Q_OBJECT

private slots:
    void testGameStarted();
    void testGamePaused();
    void testGameStopped();
    void testGameWon();
};

void TestBreakout::testGameStarted() {
    Breakout breakout;
    QVERIFY(!breakout.isGameStarted());

    breakout.startGame();
    QVERIFY(breakout.isGameStarted());
}

void TestBreakout::testGamePaused() {
    Breakout breakout;
    QVERIFY(!breakout.isGamePaused());

    breakout.pauseGame();
    QVERIFY(breakout.isGamePaused());
}

void TestBreakout::testGameStopped() {
    Breakout breakout;
    QVERIFY(!breakout.isGameStopped());

    breakout.stopGame();
    QVERIFY(breakout.isGameStopped());
}

void TestBreakout::testGameWon() {
    Breakout breakout;
    QVERIFY(!breakout.isGameWon());

    breakout.victory();
    QVERIFY(breakout.isGameWon());
}

QTEST_MAIN(TestBreakout)

#include "tests.moc"
