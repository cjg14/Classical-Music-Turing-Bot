
#include "cmpt_error.h"    
#include "Chatbot.h"       
#include <iostream>        
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <chrono>
#include <ctime>     
#include <cassert>
using namespace std;

class Turing_bot : public Chatbot {
private:
    string nm;
    string msg;
    string reply;

    struct composers_t {
        string comp_name;
        vector<string> pieces;
    }; 
    //Main Memory
    const vector<composers_t> composers = {
        {"bach", {"\"Prelude and Fugue in C minor\""}}, 
        {"beethoven", {"\"Moonlight Sonata\"", "\"Pathetique Sonata\"", "\"Symphony in G Minor\"", "\"Fur Elise\""}},
        {"chopin", {"\"Minute Waltz\"", "\"Ballade\"", "\"Nocturne in G Minor\"", "\"Winter Wind Etude\"", "\"Revolution Etude\""}},
        {"debussy", {"\"Clair de lune", "\"La fille aux cheveux de lin\"", "\"Arabesque\""}},
        {"liszt", {"\"Liebestraum\""}},
        {"mozart", {"\"Twinkle Twinkle Little Star\""}},
        {"vivaldi", {"\"Four Seasons\""}}
    }; 
//Helper Methods:
    //Checks if msg is a question or statement
    bool is_a_question (const vector<string>& substrs) {
        for (string s : substrs) {
            for (char c : s) {
                if (c == '?') {
                    return true;
                }
            }
        }
        return false;
    }
    void remove_special_characters (vector<string>& substrs) {
        vector<string> new_version;
        string temp;
        for (string s : substrs) {
            for (char c : s) {
                if (isalpha(c)) {
                    temp.push_back(c);
                }
            }
            new_version.push_back(temp);
            temp.clear();
        }
        substrs = new_version;
    }
    //Prints the names of composers in proper format
    string to_formal (const string& s) {
        string str; 
        for (int i = 0; i < s.size(); i++) {
            if (i == 0) {
                str.push_back(toupper(s.at(i)));
            } else {
                str.push_back(s.at(i));
            }
        }
        return str;
    }
//Generating vector<string> of helpers
    vector<string> generate_names () {
        vector<string> composer_names;
        for (composers_t comp : composers) {
            composer_names.push_back(comp.comp_name);
        }
        sort(composer_names.begin(), composer_names.end());
        return composer_names;
    }
    vector<string> generate_substrs (const string& s) {
        string temp;
        vector<string> broken;
        vector<char> chars;
        for (char c : s) {
            
            if (isalpha(c) || c == ' ' || c == '?') {
                chars.push_back(c);
            }
        }
        int count = 0;
        for (char ch : chars) {
            count++;
            if (ch != ' ') {
                temp.push_back(tolower(ch));
            }
            if (ch == ' ' || count == chars.size()) {
                broken.push_back(temp);
                temp.clear();
            }
        }
        return broken;
    }
    
//Picking random() strings:
    string pick_starting_question () {
        vector<string> questions = {
            "Who is your favourite composer?",
            "Do you like classical music?",
            "Do you know any classical composers?"
        };
        int random_index = rand() % questions.size();
        string quest = questions.at(random_index);
        return quest;
    }
    string pick_a_piece (const string& name) {
        string piece;
        for (composers_t composer : composers) {
            if (composer.comp_name == name) {
                int rand_index = rand() % composer.pieces.size();
                piece = composer.pieces.at(rand_index);
                break;
            }
        }
        return piece;
    }
    string pick_compliment () {
        vector<string> compliments = {"beautiful", "remarkable", "stunning", "extraordinary", "astonishing", "marvelous", "incredible", "astounding"};
        int rand_index = rand() % compliments.size();
        string compliment = compliments.at(rand_index);
        return compliment;
    }
    string pick_reaction () {
        vector<string> reactions = {"Hehehe", "Oooo",  "Ohhh", "Hahaha", "Yes!", "Yeee :D"};
        int rand_index = rand() % reactions.size();
        string reaction = reactions.at(rand_index);
        return reaction;
    }
    string pick_general_response () {
        vector<string> gen_response = {
            "Eyyy",
            ":DDD niceee", 
            "cool :^)",
            "aight mate B)",
            "dopee",
            "poggg",
            "ayyyeee",
            "interesting dude",
            "nice one",
            "POGGIESSSS",
            "ok dude"
        };
        int rand_index = rand() % gen_response.size();
        string response = gen_response.at(rand_index);
        return response;
    }
    string pick_backup_response () {
        vector<string> back_up {
            "Oh what's this? Never heard of it before. ",
            "Cool, never came across that though, mind to share a bit of your wisdom? :))",
            "Oooo interesting, never heard of anything like that before. You mind spilling a bit of wisdom? :DD",
            "sorry dude, my smol brain cannot allocate this in the back of my mind. Mind to share ;)?",
            "Please explain!! :DD I don't seem to understand :("
        };
        string response = back_up.at(rand() % back_up.size());
        return response;
    }
    string pick_composer_question (const string& composer_name) {
        string question;
        vector<string> known_composer_questions = {
            "What pieces do you like from " + to_formal(composer_name) + "?",
            "Have you encountered " + to_formal(composer_name) + "\'s " + pick_a_piece(composer_name) + "?",
            "Do you like " + to_formal(composer_name) + "\'s " + pick_a_piece(composer_name) + "?",
            "Don't you think " + to_formal(composer_name) + "\'s " + pick_a_piece(composer_name) + " is " + pick_compliment() + "?"
        };
        int rand_index = rand() % known_composer_questions.size();
        question = known_composer_questions.at(rand_index);
        return question;
    }
    string pick_composer_reaction (const string& composer_name) {
        vector<string> composer_responses = {
            pick_reaction() + ", I love " + pick_a_piece(composer_name) + " by " + to_formal(composer_name) + "!",
            pick_reaction() + ", " + pick_a_piece(composer_name) + " by " + to_formal(composer_name) + " is " + pick_compliment() + "!",
            "I listen to " + to_formal(composer_name) + "\'s " + pick_a_piece(composer_name) + " all the time!",
            "I love " + to_formal(composer_name) + "\'s pieces. They are absolutely " + pick_compliment() + "!"
        };
        return composer_responses.at(rand() % composer_responses.size());
    }

//Compiling strings to generate a response:
   string response_to_statement (const vector<string>& substrs, const vector<string>& composer_names) {
        string response = "";
        //If it recognizes a composer, then it asks question on it 
        for (string name : composer_names) {
            bool has_composer = binary_search(substrs.begin(), substrs.end(), name);
            if (has_composer) {
                response = pick_composer_question(name);
                break;
            } else {
                response = pick_general_response();
            } 
        }
        return response;
    }
    string response_to_question (const vector<string>& substrs, const vector<string>& composer_names) {
        string response = "";
        //if it recognizes a composer, it reacts on it 
        for (string name : composer_names) {
            bool has_composer = binary_search(substrs.begin(), substrs.end(), name);
            if (has_composer) {
                response = pick_composer_reaction(name);
                break;
            } else {
                response = pick_backup_response();
            }
        }
        return response;
    }
    string generate_response (vector<string>& substrs, const vector<string>& composer_names) {
        string reply;
        bool is_question = is_a_question(substrs);
        remove_special_characters(substrs);
        if (is_question) {
            reply = response_to_question(substrs, composer_names);
        } else {
            reply = response_to_statement(substrs, composer_names);
        }
        return reply;
    }
public: 
    Turing_bot(string n) : nm(n) {srand(time(nullptr));}

    void tell (const string& s) {msg = s;}
    string get_reply () {
        if (msg == "") {
            reply = pick_starting_question();
        } else {
            vector <string> substr = generate_substrs(msg);
            vector<string> names = generate_names();
            sort(substr.begin(), substr.end());
            reply = generate_response(substr, names);
        }
        return reply;
    }
    string name() const {
        return nm;
    }
};

void converse(Chatbot* a, Chatbot* b, int max_turns = 50) {
  for(int turn = 1; turn <= max_turns; turn++) {
    string a_msg = a->get_reply();
    cout << "(" << turn << ") " << a->name() << ": " << a_msg << "\n";
    
    turn++;
    if (turn > max_turns) return;

    b->tell(a_msg);
    string b_msg = b->get_reply();

    cout << "(" << turn << ") " << b->name() << ": " << b_msg << "\n";
    a->tell(b_msg);
  } // for
}
int main () {}
