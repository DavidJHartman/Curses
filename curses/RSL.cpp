#include "RSL.h"

namespace RSL
{
std::string getStringData(std::string fileName, std::string dataToGet)
{
    srand(time(NULL));
    bool foundDatatype = false;
    bool foundDataMember = false;
    bool inArray = false;

    std::vector<std::string> colorContainer;


    std::string dataType = GET_FORMATTED_TYPE(&dataToGet); // GET OBJECT NAME (eg: human, goblin)
    std::string dataMember = GET_FORMATTED_TYPE(&dataToGet); // GET MEMBER OF OBJECT

    std::string line;
    std::ifstream loadFile(fileName);

    if ( loadFile.is_open() ){
        while ( !loadFile.eof() ){
            while ( getline( loadFile , line ) ){
                std::string LINE_READING;
                for (char _c : line){
                    if (_c == '\t' or _c == '}'){
                        inArray = false;
                        continue;
                    }

                    if (_c == '{' and foundDataMember == true){
                        inArray = true;
                        continue;
                    }

                    if (inArray == true){
                        if (_c == ':'){
                            colorContainer.push_back(LINE_READING);
                            LINE_READING.clear();
                            continue;
                        }
                    }

                    if (foundDataMember == true and _c == ';'){
                        if (colorContainer.size()!=0){
                            return colorContainer[rand()%colorContainer.size()];
                        }
                        return LINE_READING;
                    }

                    LINE_READING+=_c;

                    if (foundDatatype==false){
                        if (_c == ']'){

                            if (LINE_READING == dataType){
                                foundDatatype = true;
                                LINE_READING.clear();
                            }
                        }
                    }

                    if (foundDatatype==true){
                        if (_c == ']'){

                            if (LINE_READING == dataMember){
                                foundDataMember=true;
                                LINE_READING.clear();
                            }
                        }
                    }

                }
            }
        }
    }
}

int getIntData(std::string fileName, std::string dataToGet)
{
    bool foundDatatype = false;
    bool foundDataMember = false;


    std::string dataType = GET_FORMATTED_TYPE(&dataToGet); // GET OBJECT NAME (eg: human, goblin)
    std::string dataMember = GET_FORMATTED_TYPE(&dataToGet); // GET MEMBER OF OBJECT

    std::string line;
    std::ifstream loadFile(fileName);

    if ( loadFile.is_open() ){
        while ( !loadFile.eof() ){
            while ( getline( loadFile , line ) ){
                std::string LINE_READING;
                for (char _c : line){

                    if (_c == '\t'){
                        continue;
                    }

                    if (foundDataMember == true and _c == ';'){
                        std::stringstream ss;
                        int convertedInt;
                        ss << LINE_READING;
                        ss>>convertedInt;
                        return convertedInt;
                    }

                    LINE_READING+=_c;

                    if (foundDatatype==false){
                        if (_c == ']'){

                            if (LINE_READING == dataType){
                                foundDatatype = true;
                                LINE_READING.clear();
                            }
                        }
                    }

                    if (foundDatatype==true){
                        if (_c == ']'){

                            if (LINE_READING == dataMember){
                                foundDataMember=true;
                                LINE_READING.clear();
                            }
                        }
                    }
                }
            }
        }
    }
}

std::vector<bodyPart*> getBodyData(std::string fileName, std::string dataToGet)
{
    bool foundDatatype = false;
    bool foundDataMember = false;
    bool foundQuantity = false;
    std::vector<bodyPart*> body;

    int quantity;
    int weight;


    std::string dataType = GET_FORMATTED_TYPE(&dataToGet); // GET OBJECT NAME (eg: human, goblin)
    std::string dataMember = GET_FORMATTED_TYPE(&dataToGet); // GET MEMBER OF OBJECT

    std::string line;
    std::ifstream loadFile(fileName);

    if ( loadFile.is_open() ){
        while ( !loadFile.eof() ){
            while ( getline( loadFile , line ) ){
                std::string LINE_READING;
                for (char _c : line){

                    if (_c == '\t' or _c == '{' or _c == '}'){
                        continue;
                    }
                    if (foundDataMember == true){
                        if (_c == ','){
                            std::stringstream ss;
                            ss << LINE_READING;
                            if (foundQuantity == false){
                                ss >> quantity;
                                foundQuantity = true;
                            }
                            else{
                                ss >> weight;
                                foundQuantity = false;
                            }
                            LINE_READING.clear();
                            continue;
                        }
                        else if(_c == ':'){
                            for (int i=0;i<quantity;i++){
                                if (LINE_READING == "head"){body.push_back(new head(weight));}
                                else if (LINE_READING =="eye"){body.push_back(new eye(weight, i));}
                                else if (LINE_READING == "neck"){body.push_back(new neck(weight));}
                                else if (LINE_READING=="torso"){body.push_back(new torso(weight));}
                                else if (LINE_READING =="arm"){body.push_back(new arm(weight, i));}
                                else if (LINE_READING =="leg"){body.push_back(new leg(weight, i));}
                            }
                            LINE_READING.clear();
                            continue;
                        }
                    }

                    if (foundDataMember == true and _c == ';'){
                        return body;
                    }

                    LINE_READING+=_c;

                    if (foundDatatype==false){
                        if (_c == ']'){

                            if (LINE_READING == dataType){
                                foundDatatype = true;
                                LINE_READING.clear();
                            }
                        }
                    }

                    if (foundDatatype==true and foundDataMember == false){
                        if (_c == ']'){

                            if (LINE_READING == dataMember){
                                foundDataMember=true;
                                LINE_READING.clear();
                            }
                        }

                    }
                }
            }
        }
    }
}

sf::Texture getTextureData(std::string fileName, std::string dataToGet)
{
    bool foundDatatype = false;
    bool foundDataMember = false;
    bool foundQuantity = false;
    bool foundTexture = false;
    std::vector<int> intRectangle;

    sf::Texture whatever;

    std::string dataType = GET_FORMATTED_TYPE(&dataToGet); // GET OBJECT NAME (eg: human, goblin)
    std::string dataMember = GET_FORMATTED_TYPE(&dataToGet); // GET MEMBER OF OBJECT

    std::string line;
    std::ifstream loadFile(fileName);


    if ( loadFile.is_open() ){
        while ( !loadFile.eof() ){
            while ( getline( loadFile , line ) ){
                std::string LINE_READING;

                for (char _c : line){

                    if (_c == '\t' or _c == '{' or _c == '}'){
                        continue;
                    }
                    if (foundDataMember == true){
                        if (_c == ',' and foundTexture == false){
                            fileName = "data/textures/" + LINE_READING;


                            LINE_READING.clear();
                            foundTexture = true;

                            continue;
                        }
                        if (foundTexture == true and _c == ':'){

                            std::stringstream ss;
                            ss << LINE_READING;

                            int temp;
                            ss >> temp;



                            intRectangle.push_back(temp);

                            LINE_READING.clear();
                            continue;
                        }
                    }

                    if (foundDataMember == true and _c == ';'){
                        sf::Texture temp;
                        temp.loadFromFile(fileName,sf::IntRect(intRectangle[1],intRectangle[0],16,16));

                        return temp;
                    }

                    LINE_READING+=_c;

                    if (foundDatatype==false){
                        if (_c == ']'){

                            if (LINE_READING == dataType){
                                foundDatatype = true;
                                LINE_READING.clear();
                            }
                        }
                    }

                    if (foundDatatype==true and foundDataMember == false){
                        if (_c == ']'){

                            if (LINE_READING == dataMember){
                                foundDataMember=true;
                                LINE_READING.clear();
                            }
                        }

                    }
                }
            }
        }
    }
}

std::vector<material> unloadMaterials(std::string fileName)
{

    bool foundDatatype = false;
    bool foundDataMember = false;
    std::vector<int> intRectangle;

    std::vector<material> materials;

    std::string dataMember;

    sf::Texture whatever;

    std::string line;
    std::ifstream loadFile(fileName);


    if ( loadFile.is_open() ){
        while ( !loadFile.eof() ){
            while ( getline( loadFile , line ) ){
                std::string LINE_READING;

                if (line == "[START]"){
                    foundDatatype = true;
                    materials.resize(materials.size()+1);
                    continue;
                }

                if (line == "[END]"){
                    foundDatatype = false;
                }

                if (foundDatatype == true){
                    for (char _c : line){
                            if (_c == '\t'){
                                continue;
                            }

                        if (LINE_READING == "[NAME]" or LINE_READING == "[TEXTURE]"){
                            foundDataMember = true;
                            dataMember = LINE_READING;
                            LINE_READING.clear();
                        }

                        if (foundDataMember == true){
                            if (_c == ';' or _c == ','){
                                if (dataMember == "[NAME]"){ materials[materials.size()-1].name = LINE_READING;}
                                if (dataMember == "[TEXTURE]"){ materials[materials.size()-1].texture = RSL::getTextureData(fileName, materials[materials.size()-1].name + ".texture");}

                                dataMember.clear();
                                LINE_READING.clear();

                            }
                        }
                        LINE_READING += _c;
                    }
                }
            }
        }
    }
    return materials;
}

std::string GET_FORMATTED_TYPE(std::string *typeToFix)
{
    std::string tempStorage;
    std::string dataType;
    dataType+="[";
    for (char _c : *typeToFix){
        if (_c!='.'){
            tempStorage+=toupper(_c);
        }
        else if (_c == '.' or _c == ']'){
            break;
        }
    }
    typeToFix->erase(0,tempStorage.size()+1);
    return dataType + tempStorage + ']';
}

}
