#include <vector>

#include "gtest/gtest.h"

#include "test_setup.cpp"

namespace test {
  TEST(SUITE, CASE_1) {
    test(
        "6\n"
        "CHANGE_CAPITAL RussianEmpire Petrograd\n"
        "RENAME RussianEmpire RussianRepublic\n"
        "ABOUT RussianRepublic\n"
        "RENAME RussianRepublic USSR\n"
        "CHANGE_CAPITAL USSR Moscow\n"
        "DUMP\n",

        "Introduce new country RussianEmpire with capital Petrograd\n"
        "Country RussianEmpire with capital Petrograd has been renamed to RussianRepublic\n"
        "Country RussianRepublic has capital Petrograd\n"
        "Country RussianRepublic with capital Petrograd has been renamed to USSR\n"
        "Country USSR has changed its capital from Petrograd to Moscow\n"
        "USSR/Moscow\n"
    );
  }

  TEST(SUITE, CASE_2) {
    test(
        "24\n"
        "RENAME FakeCountry FarFarAway\n"
        "ABOUT FarFarAway\n"
        "DUMP\n"
        "CHANGE_CAPITAL TsardomOfRussia Moscow\n"
        "CHANGE_CAPITAL TsardomOfRussia Moscow\n"
        "CHANGE_CAPITAL ColonialBrazil Salvador\n"
        "CHANGE_CAPITAL TsardomOfRussia SaintPetersburg\n"
        "RENAME TsardomOfRussia RussianEmpire\n"
        "CHANGE_CAPITAL RussianEmpire Moscow\n"
        "CHANGE_CAPITAL RussianEmpire SaintPetersburg\n"
        "CHANGE_CAPITAL ColonialBrazil RioDeJaneiro\n"
        "DUMP\n"
        "RENAME ColonialBrazil EmpireOfBrazil\n"
        "ABOUT RussianEmpire\n"
        "RENAME EmpireOfBrazil UnitedStatesOfBrazil\n"
        "CHANGE_CAPITAL RussianEmpire Petrograd\n"
        "RENAME RussianEmpire RussianRepublic\n"
        "RENAME RussianRepublic USSR\n"
        "CHANGE_CAPITAL USSR Moscow\n"
        "CHANGE_CAPITAL UnitedStatesOfBrazil Brasilia\n"
        "RENAME UnitedStatesOfBrazil FederativeRepublicOfBrazil\n"
        "ABOUT RussianEmpire\n"
        "DUMP\n"
        "RENAME USSR USSR\n",

        "Incorrect rename, skip\n"
        "Country FarFarAway doesn't exist\n"
        "There are no countries in the world\n"
        "Introduce new country TsardomOfRussia with capital Moscow\n"
        "Country TsardomOfRussia hasn't changed its capital\n"
        "Introduce new country ColonialBrazil with capital Salvador\n"
        "Country TsardomOfRussia has changed its capital from Moscow to SaintPetersburg\n"
        "Country TsardomOfRussia with capital SaintPetersburg has been renamed to RussianEmpire\n"
        "Country RussianEmpire has changed its capital from SaintPetersburg to Moscow\n"
        "Country RussianEmpire has changed its capital from Moscow to SaintPetersburg\n"
        "Country ColonialBrazil has changed its capital from Salvador to RioDeJaneiro\n"
        "ColonialBrazil/RioDeJaneiro RussianEmpire/SaintPetersburg\n"
        "Country ColonialBrazil with capital RioDeJaneiro has been renamed to EmpireOfBrazil\n"
        "Country RussianEmpire has capital SaintPetersburg\n"
        "Country EmpireOfBrazil with capital RioDeJaneiro has been renamed to UnitedStatesOfBrazil\n"
        "Country RussianEmpire has changed its capital from SaintPetersburg to Petrograd\n"
        "Country RussianEmpire with capital Petrograd has been renamed to RussianRepublic\n"
        "Country RussianRepublic with capital Petrograd has been renamed to USSR\n"
        "Country USSR has changed its capital from Petrograd to Moscow\n"
        "Country UnitedStatesOfBrazil has changed its capital from RioDeJaneiro to Brasilia\n"
        "Country UnitedStatesOfBrazil with capital Brasilia has been renamed to FederativeRepublicOfBrazil\n"
        "Country RussianEmpire doesn't exist\n"
        "FederativeRepublicOfBrazil/Brasilia USSR/Moscow\n"
        "Incorrect rename, skip\n"
    );
  }

  TEST(SUITE, CASE_3) {
    test(
      "10\n"
      "CHANGE_CAPITAL RussianEmpire Petrograd\n"
      "RENAME USSR RussianEmpire\n"
      "DUMP\n"
      "ABOUT USSR\n"
      "DUMP\n"
      "RENAME RussianEmpire RussianEmpire\n"
      "DUMP\n"
      "CHANGE_CAPITAL UnitedStatesOfBrazil Brasilia\n"
      "RENAME RussianEmpire UnitedStatesOfBrazil\n"
      "DUMP",

      "Introduce new country RussianEmpire with capital Petrograd\n"
      "Incorrect rename, skip\n"
      "RussianEmpire/Petrograd\n"
      "Country USSR doesn't exist\n"
      "RussianEmpire/Petrograd\n"
      "Incorrect rename, skip\n"
      "RussianEmpire/Petrograd\n"
      "Introduce new country UnitedStatesOfBrazil with capital Brasilia\n"
      "Incorrect rename, skip\n"
      "RussianEmpire/Petrograd UnitedStatesOfBrazil/Brasilia\n"
    );
  }
}

