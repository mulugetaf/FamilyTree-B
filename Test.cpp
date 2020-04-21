
#include "doctest.h"
#include "FamilyTree.hpp"
using namespace family;
using namespace std;

static family::Tree T ("Yosef");
static family::Tree F ("sdfsey");
#include <string>
    TEST_CASE("Test for addFather & addMother function") {
    T.addFather("Yosef", "Yaakov")   // Tells the tree that the father of Yosef is Yaakov.
	 .addMother("Yosef", "Rachel")   // Tells the tree that the mother of Yosef is Rachel.
	 .addFather("Yaakov", "Isaac")
	 .addMother("Yaakov", "Rivka")
	 .addFather("Isaac", "Avraham")
	 .addFather("Avraham", "Terah");
        //father
    CHECK(T.find("Father") == "Yaakov");
    CHECK(T.find("Father") == "Issac");
    CHECK(T.find("Father") == "Avraham");
    CHECK(T.find("Father") == "Terah");

    CHECK(T.find("FAther") == "Yaakov");
    CHECK(T.find("FATHER") == "Issac");
    CHECK(T.find("FatheR") == "Avraham");
    CHECK(T.find("FATHEr") == "Terah");
        //mother
    CHECK(T.find("Mother") == "Rachel");
    CHECK(T.find("Mother") == "Rivka");
    CHECK(T.find("Mother") == "Rachel");

    CHECK(T.find("Mother") == "Rachel");
    CHECK(T.find("MOTHER") == "Rivka");
    CHECK(T.find("MoTHer") == "Rachel");
    
}
 TEST_CASE("Test for relation function") {

    CHECK(T.relation("Yosef") == "root");
    CHECK(T.relation("Yaakov") == "father");
    CHECK(T.relation("Rachel") == "mother");
    CHECK(T.relation("Issac") == "grand father");
    CHECK(T.relation("Rivka") == "grand mother");
    CHECK(T.relation("Avraham") == "great grand father");
    CHECK(T.relation("Terah") == "great great grand father");


    CHECK(T.relation("Yako") == "unrelated");
    CHECK(T.relation("") == "unrelated");
    CHECK(T.relation("sara") == "unrelated");
    CHECK(T.relation("YakKo") == "unrelated");
    CHECK(T.relation(" -sdf") == "unrelated");
    CHECK(T.relation("saRRa") == "unrelated");
    CHECK(T.relation("YAkko") == "unrelated");
    CHECK(T.relation("") == "unrelated");
    CHECK(T.relation("sAAra") == "unrelated");

}
 TEST_CASE("Test for find function") {
    CHECK(T.find("root") == "Yosef");
    CHECK(T.find("father") == "Yaakov");
    CHECK(T.find("grand father") == "Issac");
    CHECK(T.find("grand mother") == "Rivka");
    CHECK(T.find("great grand father") == "Avraham");
    CHECK(T.find("great great grand father") == "Terah");
        
	
 
}
 TEST_CASE("throwing errors"){
    CHECK_THROWS(T.addFather("","Yaakov"));
    CHECK_THROWS(T.addFather("Yaakov",""));
    CHECK_THROWS(T.addFather("",""));
    CHECK_THROWS(T.addFather("Avi",""));
    CHECK_THROWS(T.addFather("Abi","Yaakov"));
    CHECK_THROWS(T.addFather("xyy","sara"));
    CHECK_THROWS(T.addFather("Yoseef","Yaakov"));
    CHECK_THROWS(T.addFather("Yo0sef",""));
    CHECK_THROWS(T.addFather("","Yosef"));
    CHECK_THROWS(T.addFather("Avi","  Yosef"));
    CHECK_THROWS(T.addFather("Abi","YAakove"));
    CHECK_THROWS(T.addFather("Yo0sef","sara"));
      
    CHECK_THROWS(T.addMother("","sara"));
    CHECK_THROWS(T.addMother("sara",""));
    CHECK_THROWS(T.addMother("",""));
    CHECK_THROWS(T.addMother("Rachel",""));
    CHECK_THROWS(T.addMother("Abi","sara"));
    CHECK_THROWS(T.addMother("Rachel","sara"));

    CHECK_THROWS(T.relation(""));
    CHECK_THROWS(T.relation("Yakov"));
    CHECK_THROWS(T.relation("Yosf"));
    CHECK_THROWS(T.relation("Avi"));
    CHECK_THROWS(T.relation("Abi"));
    CHECK_THROWS(T.relation("saa"));

    CHECK_THROWS(T.find(""));
    CHECK_THROWS(T.find("Yaaov"));
    CHECK_THROWS(T.find("yAKO"));
    CHECK_THROWS(T.find("Avi"));
    CHECK_THROWS(T.find("Yaa kov"));
    CHECK_THROWS(T.find("sra"));

    
    CHECK_THROWS(T.remove(""));
    CHECK_THROWS(T.remove("Avi"));
    CHECK_THROWS(T.remove("Yaakv"));
    CHECK_THROWS(T.remove("Issac"));
    CHECK_THROWS(T.remove("Iss ac"));
    CHECK_THROWS(T.remove("Yose"));
    CHECK_THROWS(T.remove("Yaaov"));
    CHECK_THROWS(T.remove("Yaak ov"));
    CHECK_THROWS(T.remove("xyxx"));
    CHECK_THROWS(T.remove("Avraha"));

    CHECK_THROWS(F.remove(""));
    CHECK_THROWS(F.remove("Avi"));
    CHECK_THROWS(F.remove("Yaakv"));
    CHECK_THROWS(F.remove("Is sac"));
    CHECK_THROWS(F.remove("IsSac"));
    CHECK_THROWS(F.remove("  Yose"));
    CHECK_THROWS(F.remove("Yaa-v  " ));
    CHECK_THROWS(F.remove("YaAAk ov"));
    CHECK_THROWS(F.remove("   _yxx"));
    CHECK_THROWS(F.remove("AvRRaha"));

    CHECK_THROWS(F.find(""));
    CHECK_THROWS(F.find("Yaaov"));
    CHECK_THROWS(F.find("yAKO"));
    CHECK_THROWS(F.find("Avi"));
    CHECK_THROWS(F.find("Yaa kov"));
    CHECK_THROWS(F.find("sra"));

    CHECK_THROWS(F.relation(""));
    CHECK_THROWS(F.relation("YAakov"));
    CHECK_THROWS(F.relation("YoOsf"));
    CHECK_THROWS(F.relation(" _Avi"));
    CHECK_THROWS(F.relation("A_ bi"));
    CHECK_THROWS(F.relation(" s aa"));


    CHECK_THROWS(F.addFather("  ","Yaa kov"));
    CHECK_THROWS(F.addFather("_Yaakov",""));
    CHECK_THROWS(F.addFather("",""));
    CHECK_THROWS(F.addFather("Avi",""));
    CHECK_THROWS(F.addFather("Abi","Yaakov"));
    CHECK_THROWS(F.addFather("xyy","sara"));

    //after remove yosef tree is null 
    T.remove("Yosef");

    CHECK_THROWS(T.find(" Father"));
    CHECK_THROWS(T.find("FATher"));
    CHECK_THROWS(T.find("Mothe"));
    
    CHECK_THROWS(T.find("root"));
    CHECK_THROWS(T.find("father"));
    CHECK_THROWS(T.find("grand father"));
    CHECK_THROWS(T.find("grand mother") );
    CHECK_THROWS(T.find("great grand father"));
    CHECK_THROWS(T.find("great great grand father"));
 }
