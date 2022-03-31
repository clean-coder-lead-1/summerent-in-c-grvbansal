#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "typewise-alert.h"

/*Below test cases covers - classifyTemperatureBreach and that shall also cover inferBreach*/
TEST_CASE("classify the breach according to cooling type and temperature in degree celsius") {

  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, 25) == NORMAL);
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, 25) == NORMAL);
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, 25) == NORMAL);

  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, -5) == TOO_LOW);
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, -5) == TOO_LOW);
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, -5) == TOO_LOW);
  
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, 37) == TOO_HIGH);
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, 37) == NORMAL);
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, 37) == NORMAL);

  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, 43) == TOO_HIGH);
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, 43) == NORMAL);
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, 43) == TOO_HIGH);

  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, 50) == TOO_HIGH);
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, 50) == TOO_HIGH);
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, 50) == TOO_HIGH);
}

/*Below test cases Covers - checkAndAlert*/
TEST_CASE("Check for Alert to controller") {
  AlertTarget test_alertTarget;
  BatteryCharacter test_batteryChar;
  test_batteryChar.coolingType = PASSIVE_COOLING;
  test_alertTarget = TO_CONTROLLER;
  REQUIRE(test_alertTarget == TO_CONTROLLER);
  checkAndAlert(test_alertTarget, test_batteryChar, 37);
}
TEST_CASE("Check for Alert via Email") {
  AlertTarget test_alertTarget;
  BatteryCharacter test_batteryChar;
  test_batteryChar.coolingType = MED_ACTIVE_COOLING;
  test_alertTarget = TO_EMAIL;
  REQUIRE(test_alertTarget == TO_EMAIL);
  checkAndAlert(test_alertTarget, test_batteryChar, 43);
}

/*Below test case Covers - sendToController*/
TEST_CASE("Check for Send to controller") {
  BreachType test_breachType = TOO_HIGH;

  REQUIRE(test_breachType == TOO_HIGH);

  sendToController(TOO_HIGH);
}

/*Below test cases Covers - sendToEmail*/
TEST_CASE("Check for Send via Email/TOO_HIGH") {
  BreachType test_breachType = TOO_HIGH;
  REQUIRE(test_breachType==TOO_HIGH);
  sendToEmail(TOO_HIGH);
}

TEST_CASE("Check for Send via Email/TOO_LOW") {
  BreachType test_breachType = TOO_LOW;
  REQUIRE(test_breachType == TOO_LOW);
  sendToEmail(TOO_LOW);
}

TEST_CASE("Check for Send via Email/NORMAL") {
  BreachType test_breachType = NORMAL;
  REQUIRE(test_breachType == NORMAL);
  sendToEmail(NORMAL);
}
