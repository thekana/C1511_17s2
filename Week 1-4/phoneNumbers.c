//Debugging phone number code
//Edited by King (z517670) and Maerry(z5142102)
//Tutor Zain (F09A)
//2017-08-11


// Decode a international calling prefix into a country name,
// See this Wikipedia page for more info: 
// https://en.wikipedia.org/wiki/List_of_country_calling_codes
//
// Written by Julian Saknussemm 2017-08-06

#include <stdio.h>
#include <stdlib.h>

// Different code series
void series2(void);
void series21(void);
void series22(void);
void series23(void);
void series24(void);
void series25(void);
void series26(void);
void series29(void);
void series3(void);
void series35(void);
void series37(void);
void series38(void);
void series4(void);
void series42(void);
void series5(void);
void series50(void);
void series59(void);
void series599(void);
void series6(void);
void series67(void);
void series68(void);
void series69(void);
void series8(void);
void series80(void);
void series85(void);
void series87(void);
void series88(void);
void series9(void);
void series96(void);
void series97(void);
void series99(void);

// Get a digit as a number less than 10
int getDigit(void);

int main(int argc, char *argv[]) {
    
    printf("Enter in an international phone number without a '+' (e.g. 61 412 345 678): ");
    int firstDigit = getDigit();

    printf("This number is ");
    if (firstDigit == 1) {
        //Figuring out where in north america is too hard
        printf("part of the North American Numbering Plan.\n");
        return EXIT_SUCCESS;
    } else {
        // Everywhere else we can say the exact country
        printf("from ");
    }

    // Deal with numbers that start with something other than 1
    if (firstDigit == 2) {
        series2();
    } else if (firstDigit == 3) {
        series3();
    } else if (firstDigit == 4) {
        series4();
    } else if (firstDigit == 5) {
        series5();
    } else if (firstDigit == 6) {
        series6();
    } else if (firstDigit == 7) {
        printf("Russia, Kazakhstan or Abkhazia");
    } else if (firstDigit == 8) {
        series8();
    } else if (firstDigit == 9) {
        series9();
    } else {
        printf("nowhere");
    }

    // End the sentence
    printf(".\n");

    return EXIT_SUCCESS;
}

void series2(void) {
    int secondDigit = getDigit();

    if (secondDigit == 0) {
        printf("Egypt");
    } else if (secondDigit == 1) {
        series21();
    } else if (secondDigit == 2) {
        series22();
    } else if (secondDigit == 3) {
        series23();
    } else if (secondDigit == 4) {
        series24();
    } else if (secondDigit == 5) {
        series25();
    } else if (secondDigit == 6) {
        series26();
    } else if (secondDigit == 7) {
        printf("South Africa");
    } else if (secondDigit == 9) {
        series29();
    } else {
        printf("nowehere");
    }

}

void series21(void) {
    int thirdDigit = getDigit();

    if (thirdDigit == 1) {
        printf("South Sudan");
    } else if (thirdDigit == 2) {
        printf("Morocco");
    } else if (thirdDigit == 3) {
        printf("Algeria");
    } else if (thirdDigit == 6) {
        printf("Tunisia");
    } else if (thirdDigit == 8) {
        printf("Libya");
    } else {
        printf("nowhere");
    }
}

void series22(void) {
    int thirdDigit = getDigit();

    if (thirdDigit == 0) {
        printf("Gambia");
    } else if (thirdDigit == 1) {
        printf("Senegal");
    } else if (thirdDigit == 2) {
        printf("Mauritania");
    } else if (thirdDigit == 3) {
        printf("Mali");
    } else if (thirdDigit == 4) {
        printf("Guinea");
    } else if (thirdDigit == 5) {
        printf("Ivory Coast");
    } else if (thirdDigit == 6) {
        printf("Burkina Faso");
    } else if (thirdDigit == 7) {
        printf("Niger");
    } else if (thirdDigit == 8) {
        printf("Togo");
    } else {
        printf("Benin");
    }
}

void series23(void) {
    int thirdDigit = getDigit();

    if (thirdDigit == 0) {
        printf("Mauritius");
    } else if (thirdDigit == 1) {
        printf("Liberia");
    } else if (thirdDigit == 2) {
        printf("Sierra Leone");
    } else if (thirdDigit == 3) {
        printf("Ghana");
    } else if (thirdDigit == 4) {
        printf("Nigeria");
    } else if (thirdDigit == 5) {
        printf("Chad");
    } else if (thirdDigit == 6) {
        printf("Central African Republic");
    } else if (thirdDigit == 7) {
        printf("Cameroon");
    } else if (thirdDigit == 8) {
        printf("Cape Verde");
    } else {
        printf("SÃ£o TomÃ© and PrÃ­ncipe");
    }
}

void series24(void) {
    int thirdDigit = getDigit();

    if (thirdDigit == 0) {
        printf("Equatorial Guinea");
    } else if (thirdDigit == 1) {
        printf("Gabon");
    } else if (thirdDigit == 2) {
        printf("Republic of the Congo");
    } else if (thirdDigit == 3) {
        printf("Democratic Republic of the Congo");
    } else if (thirdDigit == 4) {
        printf("Angola");
    } else if (thirdDigit == 5) {
        printf("Guinea-Bissau");
    } else if (thirdDigit == 6) {
        printf("British Indian Ocean Territory");
    } else if (thirdDigit == 7) {
        printf("Ascension Island");
    } else if (thirdDigit == 8) {
        printf("Seychelles");
    } else {
        printf("Sudan");
    }
}

void series25(void) {
    int thirdDigit = getDigit();

    if (thirdDigit == 0) {
        printf("Rwanda");
    } else if (thirdDigit == 1) {
        printf("Ethiopia");
    } else if (thirdDigit == 2) {
        printf("Somalia");
    } else if (thirdDigit == 3) {
        printf("Djibouti");
    } else if (thirdDigit == 4) {
        printf("Kenya");
    } else if (thirdDigit == 5) {
        printf("Tanzania or Zanzibar");
    } else if (thirdDigit == 6) {
        printf("Uganda");
    } else if (thirdDigit == 7) {
        printf("Burundi");
    } else if (thirdDigit == 8) {
        printf("Mozambique");
    } else {
        printf("nowhere");
    }
}

void series26(void) {
    int thirdDigit = getDigit();

    if (thirdDigit == 0) {
        printf("Zambia");
    } else if (thirdDigit == 1) {
        printf("Madagascar");
    } else if (thirdDigit == 2) {
        printf("RÃ©union Mayotte");
    } else if (thirdDigit == 3) {
        printf("Zimbabwe");
    } else if (thirdDigit == 4) {
        printf("Namibia");
    } else if (thirdDigit == 5) {
        printf("Malawi");
    } else if (thirdDigit == 6) {
        printf("Lesotho");
    } else if (thirdDigit == 7) {
        printf("Botswana");
    } else if (thirdDigit == 8) {
        printf("Swaziland");
    } else {
        printf("Comoros");
    }
}

void series29(void) {
    int thirdDigit = getDigit();

    if (thirdDigit == 0) {
        printf("Saint Helena or Tristan da Cunha");
    } else if (thirdDigit == 1) {
        printf("Eritrea");
    } else if (thirdDigit == 7) {
        printf("Aruba");
    } else if (thirdDigit == 8) {
        printf("Faroe Islands");
    } else if (thirdDigit == 9) {
        printf("Greenland");
    } else {
        printf("nowhere");
    }
}

void series3(void) {
    int secondDigit = getDigit();

    if (secondDigit == 0) {
        printf("Greece");
    } else if (secondDigit == 1) {
        printf("Netherlands");
    } else if (secondDigit == 2) {
        printf("Belgium");
    } else if (secondDigit == 3) {
        printf("France");
    } else if (secondDigit == 4) {
        printf("Spain");

    }

    if (secondDigit == 5) {
        series35();
    }

    if (secondDigit == 6) {
        printf("Hungary");
    }
    
    if (secondDigit == 7) {
        series37();
    } else if (secondDigit == 8) {
        series38();
    }
    
    if (secondDigit == 9) {
        printf("Italy or The Vatican City");
    }
}

void series35(void) {
    int thirdDigit = getDigit();

    if (thirdDigit == 0) {
        printf("Gibraltar");
    } else if (thirdDigit == 1) {
        printf("Portugal");
    } else if (thirdDigit == 2) {
        printf("Luxembourg");
    } else if (thirdDigit == 3) {
        printf("Ireland");
    } else if (thirdDigit == 4) {
        printf("Iceland");
    } else if (thirdDigit == 5) {
        printf("Albania");
    } else if (thirdDigit == 6) {
        printf("Malta");
    } else if (thirdDigit == 7) {
        printf("Cyprus");
    } else if (thirdDigit == 8) {
        printf("Finland or Ã…land Islands");
    } else {
        printf("Bulgaria");
    }
}

void series37(void) {
    int thirdDigit = getDigit();

    if (thirdDigit == 0) {
        printf("Lithuania");
    } else if (thirdDigit == 1) {
        printf("Latvia");
    } else if (thirdDigit == 2) {
        printf("Estonia");
    } else if (thirdDigit == 3) {
        printf("Moldova or Transnistria");
    } else if (thirdDigit == 4) {
        printf("Armenia or Nagorno-Karabakh");
    } else if (thirdDigit == 5) {
        printf("Belarus");
    } else if (thirdDigit == 6) {
        printf("Andorra");
    } else if (thirdDigit == 7) {
        printf("Monaco");
    } else if (thirdDigit == 8) {
        printf("San Marino");
    } else {
        printf("Vatican City");
    }
}

void series38(void) {
    int thirdDigit = getDigit();

    if (thirdDigit == 0) {
        printf("Ukraine");
    } else if (thirdDigit == 1) {
        printf("Serbia");
    } else if (thirdDigit == 2) {
        printf("Montenegro");
    } else if (thirdDigit == 3) {
        printf("Kosovo");
    } else if (thirdDigit == 5) {
        printf("Croatia");
    } else if (thirdDigit == 6) {
        printf("Slovenia");
    } else if (thirdDigit == 7) {
        printf("Bosnia and Herzegovina");
    } else if (thirdDigit == 9) {
        printf("Macedonia");
    } else {
        printf("nowhere");
    }
}

void series4(void) {
    int secondDigit = getDigit();

    if (secondDigit == 0) {
        printf("Romania");
    } else if (secondDigit == 1) {
        printf("Switzerland");
    } else if (secondDigit == 2) {
        series42();
    } else if (secondDigit == 3) {
        printf("Austria");
    } else if (secondDigit == 4) {
        printf("United Kingdom, Guernsey, Jersey, or Isle of Man");
    } else if (secondDigit == 5) {
        printf("Denmark");
    } else if (secondDigit == 6) {
        printf("Sweden");
    } else if (secondDigit == 7) {
        printf("Norway, Svalbard, or Jan Mayen");
    } else if (secondDigit == 8) {
        printf("Poland");
    } else {
        printf("Germany");
    }
}

void series42(void) {
    int thirdDigit = getDigit();

    if (thirdDigit == 0) {
        printf("Czech Republic");
    } else if (thirdDigit == 1) {
        printf("Slovakia");
    } else if (thirdDigit == 3) {
        printf("Liechtenstein");
    } else {
        printf("nowhere");
    }
}

void series5(void) {
    int secondDigit = getDigit();

    if (secondDigit == 0) {
        series50();
    }
    
    if (secondDigit == 1) {
        printf("Peru");
    } else if (secondDigit == 2) {
        printf("Mexico");
    } else if (secondDigit == 3) {
        printf("Cuba");
    } else if (secondDigit == 4) {
        printf("Argentina");
    } else if (secondDigit == 5) {
        printf("Brazil");
    } else if (secondDigit == 6) {
        printf("Chile");
    } else if (secondDigit == 7) {
        printf("Colombia");
    } else if (secondDigit == 8) {
        printf("Venezuela");
    }
    
    if (secondDigit == 9) {
        series59();
    }
}

void series50(void) {
    int thirdDigit = getDigit();

    if (thirdDigit == 0) {
        printf("Falkland Islands or South Georgia and the South Sandwich Islands");
    } else if (thirdDigit == 1) {
        printf("Belize");
    } else if (thirdDigit == 2) {
        printf("Guatemala");
    } else if (thirdDigit == 3) {
        printf("El Salvador");
    } else if (thirdDigit == 4) {
        printf("Honduras");
    } else if (thirdDigit == 5) {
        printf("Nicaragua");
    } else if (thirdDigit == 6) {
        printf("Costa Rica");
    } else if (thirdDigit == 7) {
        printf("Panama");
    } else if (thirdDigit == 8) {
        printf("Saint-Pierre and Miquelon");
    } else {
        printf("Haiti");
    }
}

void series59(void) {
    int thirdDigit = getDigit();

    if (thirdDigit == 0) {
        printf("Guadeloupe");
    } else if (thirdDigit == 1) {
        printf("Bolivia");
    } else if (thirdDigit == 2) {
        printf("Guyana");
    } else if (thirdDigit == 3) {
        printf("Ecuador");
    } else if (thirdDigit == 4) {
        printf("French Guiana");
    } else if (thirdDigit == 5) {
        printf("Paraguay");
    } else if (thirdDigit == 6) {
        printf("Martinique");
    } else if (thirdDigit == 7) {
        printf("Suriname");
    } else if (thirdDigit == 8) {
        printf("Uruguay");
    } else {
        series599();
    }
}

void series599(void) {
    int fourthDigit = getDigit();

    if (fourthDigit == 3) {
        printf("Sint Eustatius");
    } else if (fourthDigit == 4) {
        printf("Saba");
    } else if (fourthDigit == 7) {
        printf("Bonaire");
    } else if (fourthDigit == 9) {
        printf("CuraÃ§ao");
    } else {
        printf("nowhere");
    }
}

void series6(void) {
    int secondDigit = getDigit();

    if (secondDigit == 0) {
        printf("Malaysia");
    } else if (secondDigit == 1) {
        printf("Australia, Cocos Islands, or Christmas Island");
    } else if (secondDigit == 2) {
        printf("Indonesia");
    } else if (secondDigit == 3) {
        printf("Philippines");
    } else if (secondDigit == 4) {
        printf("New Zealand or the Pitcairn Islands");
    } else if (secondDigit == 5) {
        printf("Singapore");
    } else if (secondDigit == 6) {
        printf("Thailand");
    } else if (secondDigit == 7) {
        series67();
    } else if (secondDigit == 8) {
        series68();
    } else {
        series69();
    }
}

void series67(void) {
    int thirdDigit = getDigit();

    if (thirdDigit == 0) {
        printf("East Timor");
    } else if (thirdDigit == 2) {
        printf("Australian External Territories");
    } else if (thirdDigit == 3) {
        printf("Brunei");
    } else if (thirdDigit == 4) {
        printf("Nauru");
    } else if (thirdDigit == 5) {
        printf("Papua New Guinea");
    } else if (thirdDigit == 6) {
        printf("Tonga");
    } else if (thirdDigit == 7) {
        printf("Solomon Islands");
    } else if (thirdDigit == 8) {
        printf("Vanuatu");
    } else if (thirdDigit == 9) {
        printf("Fiji");
    } else {
        printf("nowhere");
    }
}

void series68(void) {
    int thirdDigit = getDigit();

    if (thirdDigit == 0) {
        printf("Palau");
    } else if (thirdDigit == 1) {
        printf("Wallis and Futuna");
    } else if (thirdDigit == 2) {
        printf("Cook Islands");
    } else if (thirdDigit == 3) {
        printf("Niue");
    } else if (thirdDigit == 5) {
        printf("Samoa");
    } else if (thirdDigit == 6) {
        printf("Kiribati");
    } else if (thirdDigit == 7) {
        printf("New Caledonia");
    } else if (thirdDigit == 8) {
        printf("Tuvalu");
    } else if (thirdDigit == 9) {
        printf("French Polynesia");
    } else {
        printf("nowhere");
    }
}

void series69(void) {
    int thirdDigit = getDigit();

    if (thirdDigit == 0) {
        printf("Tokelau");
    } else if (thirdDigit == 1) {
        printf("Federated States of Micronesia");
    } else if (thirdDigit == 2) {
        printf("Marshall Islands");
    } else {
        printf("nowhere");
    }
}

void series8(void) {
    int secondDigit = getDigit();

    if (secondDigit == 0) {
        series80();
    }
    
    if (secondDigit == 1) {
        printf("Japan");
    } else if (secondDigit == 2) {
        printf("South Korea");
    } else if (secondDigit == 4) {
        printf("Vietnam");
    } else if (secondDigit == 5) {
        series85();
    } else if (secondDigit == 6) {
        printf("China");
    } else if (secondDigit == 7) {
        series87();
    } else if (secondDigit == 8) {
        series88();
    } else {
        printf("nowhere");
    }
}

void series80(void) {
    int thirdDigit = getDigit();

    if (thirdDigit == 0) {
        printf("International Freephone");
    } else if (thirdDigit == 8) {
        printf("Shared Cost Services");
    } else {
        printf("nowhere");
    }
}

void series85(void) {
    int thirdDigit = getDigit();

    if (thirdDigit == 0) {
        printf("North Korea");
    } else if (thirdDigit == 2) {
        printf("Hong Kong");
    } else if (thirdDigit == 3) {
        printf("Macau");
    } else if (thirdDigit == 5) {
        printf("Cambodia");
    } else if (thirdDigit == 6) {
        printf("Laos");
    } else {
        printf("nowhere");
    }
}

void series87(void) {
    int thirdDigit = getDigit();

    if (thirdDigit == 0) {
        printf("Inmarsat");
    } else if (thirdDigit == 5 || thirdDigit == 6 || thirdDigit == 7) {
        printf("Maritime Mobile service");
    } else if (thirdDigit == 8) {
        printf("Universal Personal Telecommunications");
    } else {
        printf("nowhere");
    }
}

void series88(void) {
    int thirdDigit = getDigit();

    if (thirdDigit == 0) {
        printf("Bangladesh");
    } else if (thirdDigit == 1) {
        printf("Global Mobile Satellite System");
    } else if (thirdDigit == 2 || thirdDigit == 3) {
        printf("International Networks");
    } else if (thirdDigit == 6) {
        printf("Taiwan");
    } else if (thirdDigit == 8) {
        printf("OCHA");
    } else {
        printf("nowhere");
    }
}

void series9(void) {
    int secondDigit = getDigit();

    if (secondDigit == 0) {
        printf("Turkey or Northern Cyprus");
    } else if (secondDigit == 1) {
        printf("India");
    } else if (secondDigit == 2) {
        printf("Pakistan");
    } else if (secondDigit == 3) {
        printf("Afghanistan");
    } else if (secondDigit == 4) {
        printf("Sri Lanka");
    } else if (secondDigit == 5) {
        printf("Myanmar");
    } else if (secondDigit == 6) {
        series96();
    } else if (secondDigit == 7) {
        series97();
    } else if (secondDigit == 8) {
        printf("Iran");
    } else {
        series99();
    }
}

void series96(void) {
    int thirdDigit = getDigit();

    if (thirdDigit == 0) {
        printf("Maldives");
    } else if (thirdDigit == 1) {
        printf("Lebanon");
    } else if (thirdDigit == 2) {
        printf("Jordan");
    } else if (thirdDigit == 3) {
        printf("Syria");
    } else if (thirdDigit == 4) {
        printf("Iraq");
    } else if (thirdDigit == 5) {
        printf("Kuwait");
    } else if (thirdDigit == 6) {
        printf("Saudi Arabia");
    } else if (thirdDigit == 7) {
        printf("Yemen");
    } else if (thirdDigit == 8) {
        printf("Oman");
    } else {
        printf("nowhere");
    }
}

void series97(void) {
    int thirdDigit = getDigit();

    if (thirdDigit == 0) {
        printf("Palestine");
    } else if (thirdDigit == 1) {
        printf("United Arab Emirates");
    } else if (thirdDigit == 2) {
        printf("Israel");
    } else if (thirdDigit == 3) {
        printf("Bahrain");
    } else if (thirdDigit == 4) {
        printf("Qatar");
    } else if (thirdDigit == 5) {
        printf("Bhutan");
    } else if (thirdDigit == 6) {
        printf("Mongolia");
    } else if (thirdDigit == 7) {
        printf("Nepal");
    } else if (thirdDigit == 9) {
        printf("International Premium Rate Service");
    } else {
        printf("nowhere");
    }
}

void series99(void) {
    int thirdDigit = getDigit();

    if (thirdDigit == 1) {
        printf("International Telecommunications Public Correspondence Service");
    } else if (thirdDigit == 2) {
        printf("Tajikistan");
    } else if (thirdDigit == 3) {
        printf("Turkmenistan");
    } else if (thirdDigit == 4) {
        printf("Azerbaijan");
    } else if (thirdDigit == 5) {
        printf("Georgia, South Ossetia, or Abkhazia");
    } else if (thirdDigit == 6) {
        printf("Kyrgyzstan");
    } else if (thirdDigit == 8) {
        printf("Uzbekistan");
    } else {
        printf("nowhere");
    }
}

int getDigit(void) {
    int digit = getchar();

    if (digit < '0' || digit > '9') {
        printf("Invalid digit '%c'.\n", digit);
        return EXIT_FAILURE;
    }

    // Return digit as an integer
    return digit - '0';
}

