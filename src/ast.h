#pragma once
#include <string>
#include <vector>
#include <array>
#include <map>

using namespace std;

class Sound {    
public:
    string name;
    string waveform; 
    array<float, 4> envelope;

    Sound(const string& n) : name(n) {}

    void set_waveform(const string& w) {waveform = w;}
    void set_envelope(const array<float, 4>& env) {envelope = env;}
};


class Pattern {
public:
    string name;
    string sequence; //es. |xooo|xooo|
    
    Pattern(const string& n) : name(n) {}

    void set_sequence(const string& seq) {sequence = seq;}
};


class Track {
public: 
    string name;
    unsigned short bpm;
    vector<Sound*> sounds;
    map<Sound*, Pattern> patterns;

    Track(const string& n) : name(n) {}

    void set_bpm(unsigned short bpm) {this->bpm = bpm;}
    void add_sound(Sound* s) {sounds.push_back(s);}
    void assign_pattern(Sound* s, const Pattern& p);
};
