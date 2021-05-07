#include "gtest/gtest.h"
#include "messagePrinter.h"

TEST(MessagePrinterTest, basic1) 
{
	Logger logger;
	EXPECT_EQ(true, logger.shouldPrintMessage(1, "a"));
	EXPECT_EQ(false, logger.shouldPrintMessage(1, "a"));
	EXPECT_EQ(false, logger.shouldPrintMessage(2,"a"));
}

TEST(MessagePrinterTest, basic2) 
{
	Logger logger;
	EXPECT_EQ(true, logger.shouldPrintMessage(1, "foo"));
	EXPECT_EQ(true, logger.shouldPrintMessage(2,"bar"));
	EXPECT_EQ(false, logger.shouldPrintMessage(3,"foo"));
	EXPECT_EQ(false, logger.shouldPrintMessage(8,"bar"));
	EXPECT_EQ(false, logger.shouldPrintMessage(10,"foo"));
	EXPECT_EQ(true, logger.shouldPrintMessage(11,"foo"));
}

TEST(MessagePrinterTest, stress) 
{
	Logger logger;
	EXPECT_EQ(true, logger.shouldPrintMessage(1,"pea"));
	EXPECT_EQ(false, logger.shouldPrintMessage(2,"pea"));
	EXPECT_EQ(false, logger.shouldPrintMessage(3,"pea"));
	EXPECT_EQ(false, logger.shouldPrintMessage(4,"pea"));
	EXPECT_EQ(false, logger.shouldPrintMessage(5,"pea"));
	EXPECT_EQ(false, logger.shouldPrintMessage(6,"pea"));
	EXPECT_EQ(false, logger.shouldPrintMessage(7,"pea"));
	EXPECT_EQ(false, logger.shouldPrintMessage(9, "pea"));
	EXPECT_EQ(false, logger.shouldPrintMessage(10,"pea"));
	EXPECT_EQ(true, logger.shouldPrintMessage(11,"pod"));
	EXPECT_EQ(true, logger.shouldPrintMessage(12,"pea"));
	EXPECT_EQ(false, logger.shouldPrintMessage(13,"pod"));
	EXPECT_EQ(false, logger.shouldPrintMessage(14,"pod"));
	EXPECT_EQ(false, logger.shouldPrintMessage(15,"pod"));
	EXPECT_EQ(false, logger.shouldPrintMessage(16,"pod"));
	EXPECT_EQ(false, logger.shouldPrintMessage(17,"pod"));
	EXPECT_EQ(false, logger.shouldPrintMessage(18,"pod"));
	EXPECT_EQ(false, logger.shouldPrintMessage(19,"pod"));
	EXPECT_EQ(false, logger.shouldPrintMessage(20,"pod"));
	EXPECT_EQ(true, logger.shouldPrintMessage(21,"pod"));
	EXPECT_EQ(true, logger.shouldPrintMessage(22,"pea"));
	EXPECT_EQ(false, logger.shouldPrintMessage(23,"pod"));
	EXPECT_EQ(false, logger.shouldPrintMessage(24,"pea"));
	EXPECT_EQ(false, logger.shouldPrintMessage(25,"pea"));
	EXPECT_EQ(false, logger.shouldPrintMessage(26,"pea"));
	EXPECT_EQ(false, logger.shouldPrintMessage(27,"pod"));
	EXPECT_EQ(false, logger.shouldPrintMessage(28,"pea"));
	EXPECT_EQ(false, logger.shouldPrintMessage(29,"pea"));
	EXPECT_EQ(false, logger.shouldPrintMessage(30,"pea"));
	EXPECT_EQ(true, logger.shouldPrintMessage(31,"pod"));
	EXPECT_EQ(true, logger.shouldPrintMessage(32,"pea"));
}