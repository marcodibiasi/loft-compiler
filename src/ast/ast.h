#pragma once
#include <string>
#include <vector>
#include <array>
#include <map>

using namespace std;

// DATA TYPES

/*
> Sound: stores the design of a sound. 
It is declared as: 
sound name;
*/
class Sound {    
private:
    string name;
    string waveform; 
    array<float, 4> envelope;

public:
    Sound(const string& n) : name(n) {}

    void set_waveform(const string& w) {waveform = w;}
    void set_envelope(const array<float, 4>& env) {envelope = env;}
    const string& get_name() const {return name;}
    const string& get_waveform() const {return waveform;}
    const array<float, 4>& get_envelope() const {return envelope;}
};


/*
> Pattern: stores a pattern (time- and sound-independent). 
The format is |xooo|xooo| where: x = play, o = pause.
It is declared as: 
pattern name; 
*/
class Pattern {
private:
    string name;
    string sequence; 
    
public:
    Pattern(const string& n) : name(n) {}

    void set_sequence(const string& seq) {sequence = seq;}
    const string& get_name() const {return name;}
    const string& get_sequence() const {return sequence;}
};


/*
Track: pairs sound and pattern, stores the tempo and can be played.
It is declared as: 
track name;
*/
class Track {
private: 
    string name;
    float bpm;
    vector<Sound*> sounds;
    map<Sound*, Pattern> patterns;

public:
    Track(const string& n) : name(n) {}

    void set_bpm(float bpm) {this->bpm = bpm;}
    void add_sound(Sound* s) {sounds.push_back(s);}
    void assign_pattern(Sound* s, const Pattern& p);
    const string& get_name() const {return name;}
    float get_bpm() const {return bpm;}
};

/*
Par: is a parameter. It is represented by a float32.
It is declared as: 
par name; 
*/
class Par {
private:
    string name; 
    float value; 

public:
    Par(const string& n) : name(n) {}

    void set_value(float v) {value = v;}
    float get_value() const {return value;}
};


// PROGRAM COMPONENTS

/*
A section is a defined function with a fixed name 
and no passing values
*/
class Section {
private:
    string name; 

public:
    Section(const string& n) : name(n) {}

    const string& get_name() const {return name;}
    virtual ~Section() = default;
};


class SoundsSection : public Section {
private:
    vector<Sound*> sounds;

public:
    SoundsSection(const string& n) : Section(n) {}

    void add_sound(Sound* s) {sounds.push_back(s);}
};


class TracksSection : public Section {
private: 
    vector<Track*> tracks;

public:
    TracksSection(const string& n) : Section(n) {}
    
    void add_track(Track* t) {tracks.push_back(t);}
};


/*
Play section is the entry point, therefore must be unique
*/
class PlaySection : public Section {
public:
    PlaySection() : Section("play") {}
};
