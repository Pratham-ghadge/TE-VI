#include <iostream>
#include <vector>
#include <map>
#include <thread>
#include <chrono>
using namespace std;

// Rule structure
struct Rule {
    vector<string> if_all;
    string conclusion;
    string action;
};

class MedicalExpertSystem {
private:
    vector<Rule> rules;
    map<string, bool> facts;

public:
    MedicalExpertSystem() {
        // Initialize rules
        rules = {
            {{"high_fever", "cough", "tired"}, "FLU", "Take rest, drink fluids, consult doctor."},
            {{"high_fever", "body_pain"}, "INFECTION", "Visit doctor and take medicines."},
            {{"cough", "cold"}, "COMMON COLD", "Take steam and drink warm water."},
            {{"tired", "body_pain"}, "FATIGUE", "Take rest and proper diet."},
            {{"high_fever"}, "MILD FEVER", "Take paracetamol and rest."}
        };
    }

    bool ask(string question) {
        char ans;
        cout << question << " (y/n): ";
        cin >> ans;
        return (ans == 'y' || ans == 'Y');
    }

    string gather_facts() {
        cout << "=================================================\n";
        cout << "     EXPERT SYSTEM: MEDICAL DIAGNOSIS\n";
        cout << "=================================================\n";

        string name;
        cout << "Patient Name: ";
        cin >> name;

        // Ask questions
        bool fever = ask("1. Do you have high fever?");
        bool cough = ask("2. Do you have cough?");
        bool pain = ask("3. Do you have body pain?");
        bool cold = ask("4. Do you have cold/runny nose?");
        bool tired = ask("5. Do you feel tired or weak?");

        // Store facts
        facts["high_fever"] = fever;
        facts["cough"] = cough;
        facts["body_pain"] = pain;
        facts["cold"] = cold;
        facts["tired"] = tired;

        return name;
    }

    Rule inference_engine() {
        cout << "\n[Inference Engine]: Checking symptoms...\n";
        this_thread::sleep_for(chrono::seconds(1));

        for (auto rule : rules) {
            bool match = true;

            for (auto cond : rule.if_all) {
                if (facts[cond] == false) {
                    match = false;
                    break;
                }
            }

            if (match) {
                return rule;
            }
        }

        return Rule{{}, "NO MAJOR ISSUE", "You are healthy. Maintain good lifestyle."};
    }

    void run() {
        string name = gather_facts();
        Rule result = inference_engine();

        cout << "\n=================================================\n";
        cout << " FINAL MEDICAL RESULT: " << name << endl;
        cout << "=================================================\n";
        cout << "CONCLUSION : " << result.conclusion << endl;
        cout << "ACTION     : " << result.action << endl;
        cout << "=================================================\n";
    }
};

int main() {
    MedicalExpertSystem obj;
    obj.run();
    return 0;
}