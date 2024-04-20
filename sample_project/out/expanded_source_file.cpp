

enum class SoftwareType {
    CPP = 20,
    C = 11
};

struct Software {
    std::string name;
    SoftwareType type;
};


struct Person {
    std::string name;
    std::string status;
    int age;
};


void ShowMessage(std::string message) {
    std::cout << message << std::endl;
}


using std::cout, std::endl, std::string;

int main() {
    Person person = {
        .name = "Jinoyoko",
        .status = "chilled",
        .age = 22
    }

    Software codexpander = {
        .name = "CodEXpander",
        .type = SoftwareType::CPP
    };

    string greetMessage = "Hello " + codexpander.name + "!";
    ShowMessage(greetMessage);

    string infoMessage = "This " codexpander.type " software was developed by " 
        + person.name + " currently with " + person.age + " of age.\n" +
        "I'm pretty " + person.status + " with this tool."; 
    ShowMessage(infoMessage);
}
