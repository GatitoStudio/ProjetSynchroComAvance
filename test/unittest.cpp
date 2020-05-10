include "doctest.h"
include "../src/GenerateurVoiture.c"
include "../src/RondPoint.c"

TEST_CASE("Les methodes de GenerateurVoiture sont correctes"){
  //Insérer ici les variables nécessaire pour les tests

    SUBCASE("La methode CreateVoiture() est correcte"){
        REQUIRE_EQ(CreateVoiture(),0);
    }

    /*SUBCASE("La methode y() est correcte"){
        REQUIRE_EQ(y(),0);
    }*/

}

TEST_CASE("Les methodes de RondPoint sont correctes"){
  int indice,voiture = 0,5;

    SUBCASE("La methode DeplaceVoiture() est correcte"){
        REQUIRE_EQ(DeplaceVoiture(),0);
    }

    SUBCASE("La methode avanceVoiture() est correcte"){
        avanceVoiture();
        REQUIRE_EQ(voitures[0],1);
        REQUIRE_EQ(voitures[1],2);
        REQUIRE_EQ(voitures[2],3);
        REQUIRE_EQ(voitures[3],0);
    }

    SUBCASE("La methode suppressionVoiture() est correcte"){
        suppressionVoiture(indice);
        REQUIRE_EQ(voitures[indice],NULL);
    }

    SUBCASE("La methode insertionVoiture() est correcte"){
        insertionVoiture(indice,voiture);
        REQUIRE_EQ(voitures[indice],voiture);
    }

}
