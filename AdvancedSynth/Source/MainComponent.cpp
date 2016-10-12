// Music 256a / CS 476a | fall 2016
// CCRMA, Stanford University
//
// Author: Romain Michon (rmichonATccrmaDOTstanfordDOTedu)
// Description: Simple synth demonstrating how to use the STK with JUCE.

#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "stk/SineWave.h" // STK sine osc
#include "stk/BlitSaw.h" // STK sawtooth osc
#include "stk/BlitSquare.h" // STK square osc
#include "stk/ADSR.h"
#include <math.h>
#include "Smooth.h"

#define nChans 2
#define numKeys 12
#define transpose 1

using namespace stk; // required for the STK to work

class MainContentComponent :
public AudioAppComponent,
private Slider::Listener,
private Button::Listener,
private ComboBox::Listener
{
public:
    MainContentComponent()
    :   currentSampleRate (0.0),
    gain(0.0),
    oscFreq(0.0),
    modIndex(0.0),
    c_A(0.0), c_D(0.0), c_S(0.0), c_R(0.0),
    m_A(0.0), m_D(0.0), m_S(0.0), m_R(0.0)
    {
       
        setSize (1020, 230);
        setAudioChannels (0, nChans);
        
        addAndMakeVisible (frequencySlider);
        frequencySlider.setRange (50.0, 5000.0);
        frequencySlider.setValue(440);
        frequencySlider.setSliderStyle(Slider::Rotary);
        frequencySlider.setSkewFactorFromMidPoint (1500.0);
        frequencySlider.setTextBoxStyle(Slider::TextBoxBelow, false, 0,0);
        frequencySlider.addListener (this);
        
        addAndMakeVisible(frequencyLabel);
        frequencyLabel.setText ("Freq", dontSendNotification);
        frequencyLabel.attachToComponent (&frequencySlider, false);
        
        
        // OSC Selection Knob and Labels
        addAndMakeVisible(oscKnob);
        oscKnob.setRange (0, 3, 1);
        oscKnob.setSliderStyle(Slider::Rotary);
        oscKnob.setTextBoxStyle(Slider::NoTextBox, false, 0,0);
        addAndMakeVisible(sineLabel);
        addAndMakeVisible(sqrLabel);
        addAndMakeVisible(sawLabel);
        addAndMakeVisible(noiseLabel);
        addAndMakeVisible(oscName);
        sineLabel.setText("sin",dontSendNotification);
        sqrLabel.setText ("sqr", dontSendNotification);
        sawLabel.setText("saw", dontSendNotification);
        noiseLabel.setText("noise", dontSendNotification);
        oscName.setText("OSCILLATOR", dontSendNotification);
        oscKnob.addListener(this);
        
        // OSC Volume Knob and Labels
        addAndMakeVisible(oscVolumeKnob);
        addAndMakeVisible(oscVolumeLabel);
        oscVolumeKnob.setRange(0, 1);
        oscVolumeKnob.setValue(0.3);
        oscVolumeKnob.setSliderStyle(Slider::RotaryVerticalDrag);
        oscVolumeKnob.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
        oscVolumeKnob.addListener(this);

        oscVolumeLabel.setText("Volume", dontSendNotification);
        oscVolumeLabel.attachToComponent(&oscVolumeKnob, false);
        
        // Modulation Selection Knob and Labels;
        addAndMakeVisible(modSelectionKnob);
        addAndMakeVisible(modOffLabel);
        addAndMakeVisible(AMLabel);
        addAndMakeVisible(FMLabel);
        addAndMakeVisible(modSelectionLabel);
        modSelectionKnob.setRange(0, 2, 1);
        modSelectionKnob.setSliderStyle(Slider::Rotary);
        modSelectionKnob.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
        modSelectionKnob.addListener(this);
        modOffLabel.setText("off", dontSendNotification);
        AMLabel.setText("AM", dontSendNotification);
        FMLabel.setText("FM", dontSendNotification);
        modSelectionLabel.setText("MOD SELECT", dontSendNotification);

        
        // Modulation LFO Knob and Labels
        addAndMakeVisible(modKnob);
        addAndMakeVisible(modLabel);
        
        modKnob.setRange(0.01, 5000);
        modKnob.setValue(0.0);
        modKnob.setSliderStyle(Slider::Rotary);
        modKnob.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
        modKnob.addListener(this);
        modLabel.setText("Mod Freq", dontSendNotification);
        modLabel.attachToComponent(&modKnob, false);
        
        // Modulation Index Knob and Labels
        addAndMakeVisible(modIndexKnob);
        addAndMakeVisible(modIndexLabel);
        modIndexKnob.setSliderStyle(Slider::Rotary);
        modIndexKnob.setTextBoxStyle(Slider::NoTextBox, false, 40, 20);
        modIndexKnob.addListener(this);
        modIndexLabel.setText("Index", dontSendNotification);
        modIndexLabel.attachToComponent(&modIndexKnob, false);
            // BELOW: by default. AM has different settings
        modIndexKnob.setValue(1.0);
        
        // Carrier ADSR Knobs and Labels
        addAndMakeVisible(c_A_Knob);
        addAndMakeVisible(c_D_Knob);
        addAndMakeVisible(c_S_Knob);
        addAndMakeVisible(c_R_Knob);
        addAndMakeVisible(cNameLabel);
        c_A_Knob.setSliderStyle(Slider::Rotary);
        c_D_Knob.setSliderStyle(Slider::Rotary);
        c_S_Knob.setSliderStyle(Slider::Rotary);
        c_R_Knob.setSliderStyle(Slider::Rotary);
        c_A_Knob.setTextBoxStyle(Slider::NoTextBox, false, 40, 20);
        c_D_Knob.setTextBoxStyle(Slider::NoTextBox, false, 40, 20);
        c_S_Knob.setTextBoxStyle(Slider::NoTextBox, false, 40, 20);
        c_R_Knob.setTextBoxStyle(Slider::NoTextBox, false, 40, 20);
        c_A_Knob.setRange (1, 1000, 1);
        c_D_Knob.setRange (1, 5000, 1);
        c_S_Knob.setRange (0, 1);
        c_R_Knob.setRange (1, 5000, 1);
        c_A_Knob.setValue(50);
        c_D_Knob.setValue(50);
        c_S_Knob.setValue(0.8);
        c_R_Knob.setValue(50);
        c_A_Knob.addListener(this);
        c_D_Knob.addListener(this);
        c_S_Knob.addListener(this);
        c_R_Knob.addListener(this);

        c_A_Label.setText("A (ms)", dontSendNotification);
        c_D_Label.setText("D (ms)", dontSendNotification);
        c_S_Label.setText("S (level)", dontSendNotification);
        c_R_Label.setText("R (ms)", dontSendNotification);
        cNameLabel.setText("CARRIER ADSR", dontSendNotification);
        c_A_Label.attachToComponent(&c_A_Knob, false);
        c_D_Label.attachToComponent(&c_D_Knob, false);
        c_S_Label.attachToComponent(&c_S_Knob, false);
        c_R_Label.attachToComponent(&c_R_Knob, false);


        // Carrier ADSR Knobs and Labels
        addAndMakeVisible(m_A_Knob);
        addAndMakeVisible(m_D_Knob);
        addAndMakeVisible(m_S_Knob);
        addAndMakeVisible(m_R_Knob);
        addAndMakeVisible(mNameLabel);
        m_A_Knob.setSliderStyle(Slider::Rotary);
        m_D_Knob.setSliderStyle(Slider::Rotary);
        m_S_Knob.setSliderStyle(Slider::Rotary);
        m_R_Knob.setSliderStyle(Slider::Rotary);
        m_A_Knob.setTextBoxStyle(Slider::NoTextBox, false, 40, 20);
        m_D_Knob.setTextBoxStyle(Slider::NoTextBox, false, 40, 20);
        m_S_Knob.setTextBoxStyle(Slider::NoTextBox, false, 40, 20);
        m_R_Knob.setTextBoxStyle(Slider::NoTextBox, false, 40, 20);
        m_A_Knob.setRange (1, 1000, 1);
        m_D_Knob.setRange (1, 5000, 1);
        m_S_Knob.setRange (0, 1);
        m_R_Knob.setRange (1, 5000, 1);
        m_D_Knob.setSkewFactorFromMidPoint(1000);
        m_R_Knob.setSkewFactorFromMidPoint(1000);
        m_A_Knob.setValue(50);
        m_D_Knob.setValue(10);
        m_S_Knob.setValue(0.8);
        m_R_Knob.setValue(50);
        m_A_Knob.addListener(this);
        m_D_Knob.addListener(this);
        m_S_Knob.addListener(this);
        m_R_Knob.addListener(this);
        
        m_A_Label.setText("A (ms)", dontSendNotification);
        m_D_Label.setText("D (ms)", dontSendNotification);
        m_S_Label.setText("S (level)", dontSendNotification);
        m_R_Label.setText("R (ms)", dontSendNotification);
        mNameLabel.setText("MOD ADSR", dontSendNotification);
        m_A_Label.attachToComponent(&m_A_Knob, false);
        m_D_Label.attachToComponent(&m_D_Knob, false);
        m_S_Label.attachToComponent(&m_S_Knob, false);
        m_R_Label.attachToComponent(&m_R_Knob, false);
        
        // Drop Down Menu
        addAndMakeVisible(dropDown);
        addAndMakeVisible(dropDownLabel);
        dropDown.addItemList({"Bell","Brass","Clarinet", "Police"}, 1);
        dropDown.addListener(this);
        dropDownLabel.setText("Presets", dontSendNotification);
        dropDownLabel.attachToComponent(&dropDown, false);
    }
    
    ~MainContentComponent()
    {
        shutdownAudio();
    }
    
    
    
    
    
    //************************* Change GUI Size Here ********************************//
    void resized() override
    {
        const int labelColumnWidth = 80;
        const int componentsHeight = 20;
        const int toTop = 40;
        
        oscKnob.setBounds(labelColumnWidth, toTop, componentsHeight*3, componentsHeight*3);
        sineLabel.setBounds(labelColumnWidth-25,toTop+35,componentsHeight*3,componentsHeight);
        sqrLabel.setBounds(labelColumnWidth-25,toTop-5,componentsHeight*3,componentsHeight);
        sawLabel.setBounds(labelColumnWidth+55,toTop-5,componentsHeight*3,componentsHeight);
        noiseLabel.setBounds(labelColumnWidth+55,toTop+35,componentsHeight*3,componentsHeight);
        oscName.setBounds(labelColumnWidth-componentsHeight+5, toTop-componentsHeight*1.5, componentsHeight*5, componentsHeight);

        oscVolumeKnob.setBounds(labelColumnWidth+200, toTop, componentsHeight*3, componentsHeight*3);
        frequencySlider.setBounds (labelColumnWidth+100, toTop, componentsHeight*3, componentsHeight*3);
        modKnob.setBounds(labelColumnWidth+100, toTop+100, componentsHeight*3, componentsHeight*3);
        
        modSelectionKnob.setBounds(labelColumnWidth, toTop+100, componentsHeight*3, componentsHeight*3);
        modOffLabel.setBounds(labelColumnWidth-25,toTop+135,componentsHeight*3,componentsHeight);
        AMLabel.setBounds(labelColumnWidth+15,toTop+85,componentsHeight*3,componentsHeight);
        FMLabel.setBounds(labelColumnWidth+55,toTop+135,componentsHeight*3,componentsHeight);
        modSelectionLabel.setBounds(labelColumnWidth-componentsHeight+5, toTop+65, componentsHeight*5, componentsHeight);
        
        modIndexKnob.setBounds(labelColumnWidth+200, toTop+100, componentsHeight*3, componentsHeight*3);

        
        // Carrier ADSR drawing
        c_A_Knob.setBounds(labelColumnWidth+400, toTop, componentsHeight*3, componentsHeight*3);
        c_D_Knob.setBounds(labelColumnWidth+500, toTop, componentsHeight*3, componentsHeight*3);
        c_S_Knob.setBounds(labelColumnWidth+600, toTop, componentsHeight*3, componentsHeight*3);
        c_R_Knob.setBounds(labelColumnWidth+700, toTop, componentsHeight*3, componentsHeight*3);
        cNameLabel.setBounds(labelColumnWidth+300, toTop+10, componentsHeight*5, componentsHeight);
        
        // Mod ADSR drawing
        m_A_Knob.setBounds(labelColumnWidth+400, toTop+100, componentsHeight*3, componentsHeight*3);
        m_D_Knob.setBounds(labelColumnWidth+500, toTop+100, componentsHeight*3, componentsHeight*3);
        m_S_Knob.setBounds(labelColumnWidth+600, toTop+100, componentsHeight*3, componentsHeight*3);
        m_R_Knob.setBounds(labelColumnWidth+700, toTop+100, componentsHeight*3, componentsHeight*3);
        mNameLabel.setBounds(labelColumnWidth+300, toTop+110, componentsHeight*5, componentsHeight);
        
        // DropDown Menu
        dropDown.setBounds(labelColumnWidth+800, toTop, componentsHeight*5, componentsHeight);
    }
    
    /***************************** Slider Value Changed *******************************/
    void sliderValueChanged (Slider* slider) override
    {
        if (slider == &frequencySlider)
        {
            if (currentSampleRate > 0.0){
                oscFreq = frequencySlider.getValue();
                sine.setFrequency(oscFreq);
                square.setFrequency(oscFreq);
                saw.setFrequency(oscFreq);
            }
        }
        if (slider == &oscVolumeKnob)
        {
            if (currentSampleRate > 0.0){
                gain = oscVolumeKnob.getValue();
            }
        }
        if (slider == &modKnob) {
            if (currentSampleRate > 0.0)
                mod.setFrequency(modKnob.getValue());
        }
        if (slider == &modIndexKnob) {
            if (currentSampleRate > 0.0)
                modIndex = modIndexKnob.getValue();
        }
        if (slider == &oscKnob) {
            oscSelection = int(oscKnob.getValue());
        }
        if (slider == &modSelectionKnob) {
            if (modSelectionKnob.getValue() == 1.0) {
                modIndexKnob.setValue(0.2);
                modIndexKnob.setRange(0,1);
            }
            else if (modSelectionKnob.getValue() == 2.0) {
                modIndexKnob.setRange(0,2000);
                modIndexKnob.setSkewFactorFromMidPoint(200);
            }
            else {}
        }
        
        //Carrier ADSR Set Up
        if (slider == &c_A_Knob)
            carrierADSR.setAttackTime(c_A_Knob.getValue()/1000);
        if (slider == &c_D_Knob) {
            carrierADSR.setDecayTime(c_D_Knob.getValue()/1000);         }
        if (slider == &c_S_Knob)
            carrierADSR.setSustainLevel(c_S_Knob.getValue());
        if (slider == &c_R_Knob)
            carrierADSR.setReleaseTime(c_R_Knob.getValue()/1000);

        //Mod ADSR Set Up
        if (slider == &m_A_Knob)
            modADSR.setAttackTime(m_A_Knob.getValue()/1000);
        if (slider == &m_D_Knob) {
            modADSR.setDecayTime(m_D_Knob.getValue()/1000);
        }
        if (slider == &m_S_Knob)
            modADSR.setSustainLevel(m_S_Knob.getValue());
        if (slider == &m_R_Knob)
            modADSR.setReleaseTime(m_R_Knob.getValue()/1000);


    }
    
    /***************************** Button Clicked *******************************/
    void buttonClicked (Button* button) override
    {
//        if(button == &sineButton && sineButton.getToggleState()){
//            sineOnOff = 1.0;
//        }
//        else{
//            sineOnOff = 0.0;
//        }
//        if(button == &sawButton && sawButton.getToggleState()){
//            sawOnOff = 1.0;
//        }
//        else{
//            sawOnOff = 0.0;
//        }
    }
    
    /********************* Key Pressed **************************/
    bool keyPressed (const KeyPress &key) override
    {
        if(key == KeyPress('q')) {
                oscFreq = 261.63*pow(1.059463, transpose);
        }
        else if (key == KeyPress('2')) {
                oscFreq = 261.63*pow(1.059463, transpose+1);
        }
        else if (key == KeyPress('w')) {
                oscFreq = 261.63*pow(1.059463, transpose+2);
        }
        else if (key == KeyPress('3')) {
                oscFreq = 261.63*pow(1.059463, transpose+3);
        }
        else if (key == KeyPress('e')) {
                oscFreq = 261.63*pow(1.059463, transpose+4);
        }
        else if (key == KeyPress('r')) {
                oscFreq = 261.63*pow(1.059463, transpose+5);
        }
        else if (key == KeyPress('5')) {
                oscFreq = 261.63*pow(1.059463, transpose+6);
        }
        else if (key == KeyPress('t')) {
                oscFreq = 261.63*pow(1.059463, transpose+7);
        }
        else if (key == KeyPress('6')) {
                oscFreq = 261.63*pow(1.059463, transpose+8);
        }
        else if (key == KeyPress('y')) {
                oscFreq = 261.63*pow(1.059463, transpose+9);
        }
        else if (key == KeyPress('7')) {
                oscFreq = 261.63*pow(1.059463, transpose+10);
        }
        else if (key == KeyPress('u')) {
                oscFreq = 261.63*pow(1.059463, transpose+11);
        }
        else if (key == KeyPress('i')) {
                oscFreq = 261.63*pow(1.059463, transpose+12);
        }
        else if (key == KeyPress('9')) {
                oscFreq = 261.63*pow(1.059463, transpose+13);
        }
        else if (key == KeyPress('o')) {
                oscFreq = 261.63*pow(1.059463, transpose+14);
        }
        else if (key == KeyPress('0')) {
                oscFreq = 261.63*pow(1.059463, transpose+15);
        }
        else if (key == KeyPress('p')) {
                oscFreq = 261.63*pow(1.059463, transpose+16);
        }
        else if (key == KeyPress('[')) {
            oscFreq = 261.63*pow(1.059463, transpose+17);
        }
        else if (key == KeyPress('=')) {
            oscFreq = 261.63*pow(1.059463, transpose+18);
        }
        else if (key == KeyPress(']')) {
            oscFreq = 261.63*pow(1.059463, transpose+19);
        }
        else if (key == KeyPress::backspaceKey) {
            oscFreq = 261.63*pow(1.059463, transpose+20);
        }
        else if (key == KeyPress('\\')) {
            oscFreq = 261.63*pow(1.059463, transpose+21);
        }
                                 else {oscFreq = 0;}
        if (presetNum) {
            UpdateModFreq(presetNum);
        }
        if (oscOnOff == 0) {
            carrierADSR.keyOn();
            modADSR.keyOn();
            oscOnOff = 1;
        }
        
        if(oscSelection == 0)
            sine.setFrequency(oscFreq);
        else if (oscSelection == 1)
            square.setFrequency(oscFreq);
        else if (oscSelection == 2)
            saw.setFrequency(oscFreq);
        else {}
        
        return true;
    }
    
    bool keyStateChanged (bool isKeyDown) override {
        
        if (!isKeyDown && oscOnOff) {
            carrierADSR.keyOff();
            oscOnOff = 0;
        }
        return true;
    }
    
    void comboBoxChanged(ComboBox* box) override {
        if (box == &dropDown) {
            if (dropDown.getSelectedId() == 1) {
                LoadPresets(1);
                presetNum = 1;
            }
            else if (dropDown.getSelectedId() == 2) {
                LoadPresets(2);
                presetNum = 2;
            }
            else if (dropDown.getSelectedId() == 3) {
                LoadPresets(3);
                presetNum = 3;
            }
            else if (dropDown.getSelectedId() == 4) {
                LoadPresets(4);
                presetNum = 4;
            }
        }
    }
    
    void prepareToPlay (int /*samplesPerBlockExpected*/, double sampleRate) override
    {
        currentSampleRate = sampleRate;
        Stk::setSampleRate(sampleRate); // STK must know the sampling rate
        sine.setFrequency(oscFreq);
        square.setFrequency(oscFreq);
        saw.setFrequency(oscFreq);
        mod.setFrequency(modKnob.getValue());
        for(int i=0; i<4; i++){
            smooth[i].setSmooth(0.999);
        }
    }
    
    void releaseResources() override
    {
    }
    
    /***************************** Get Next Audio Block *******************************/
        void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override
    {
        float* const buffer0 = bufferToFill.buffer->getWritePointer (0, bufferToFill.startSample);
        float* const buffer1 = bufferToFill.buffer->getWritePointer (1, bufferToFill.startSample);
        
        for (int sample = 0; sample < bufferToFill.numSamples; ++sample)
        {
            float currentSample = 0.0;
                if(oscSelection == 0) {
                    if (modSelectionKnob.getValue() == 0.0) // NO modulation
                        currentSample = sine.tick()*smooth[0].tick(gain)*carrierADSR.tick();
                    else if (modSelectionKnob.getValue() == 1.0) // AM
                        currentSample = (sine.tick()*smooth[1].tick(gain)*carrierADSR.tick() * (1 + mod.tick()*smooth[3].tick(modIndex)*modADSR.tick()));
                    else if (modSelectionKnob.getValue() == 2.0) { // FM
                        sine.setFrequency(smooth[0].tick(oscFreq) + mod.tick()*smooth[3].tick(modIndex)*modADSR.tick());
                        currentSample = sine.tick()*smooth[1].tick(gain)*carrierADSR.tick();
                    }
                }
                else if (oscSelection == 1) {
                    if (modSelectionKnob.getValue() == 0.0) // NO modulation
                        currentSample = square.tick()*smooth[0].tick(gain)*carrierADSR.tick();
                    else if (modSelectionKnob.getValue() == 1.0) // AM
                        currentSample = square.tick()*smooth[1].tick(gain)*carrierADSR.tick() * (1 + mod.tick()*smooth[3].tick(modIndex)*modADSR.tick());
                    else if (modSelectionKnob.getValue() == 2.0) { // FM
                        square.setFrequency(smooth[0].tick(oscFreq) + mod.tick()*smooth[3].tick(modIndex)*modADSR.tick());
                        currentSample = square.tick()*smooth[1].tick(gain)*carrierADSR.tick();
                    }
                }
                else if(oscSelection == 2) {
                    if (modSelectionKnob.getValue() == 0.0) // NO modulation
                        currentSample = saw.tick()*smooth[3].tick(gain)*carrierADSR.tick();
                    else if (modSelectionKnob.getValue() == 1.0) // AM
                        currentSample = saw.tick()*smooth[1].tick(gain)*carrierADSR.tick() * (1 + mod.tick()*smooth[3].tick(modIndex)*modADSR.tick());
                    else if (modSelectionKnob.getValue() == 2.0) { // FM
                        saw.setFrequency(smooth[0].tick(oscFreq) + mod.tick()*smooth[3].tick(modIndex)*modADSR.tick());
                        currentSample = saw.tick()*smooth[1].tick(gain)*carrierADSR.tick();
                    }
                }
                
                else if(oscSelection == 3) {
                    currentSample = (random.nextFloat()*2-1)*gain*carrierADSR.tick();
                }
                else {}
            
                // Limiter
                if (currentSample >= 1)
                    currentSample = 0.99;
                else if (currentSample <=-1)
                    currentSample = -0.99;

            buffer0[sample] = currentSample; // filling output buffer
            buffer1[sample] = currentSample; // filling output buffer
            
            
        }
    }
    
    
private:
    Slider frequencySlider;
    Slider gainSlider, oscKnob, oscVolumeKnob, modSelectionKnob, modKnob, modIndexKnob;
    Slider c_A_Knob, c_D_Knob, c_S_Knob, c_R_Knob; //Carrier
    Slider m_A_Knob, m_D_Knob, m_S_Knob, m_R_Knob; //Modulator

    ADSR carrierADSR, modADSR;
    
    Label frequencyLabel;
    Label gainLabel;
    Label sineLabel, sqrLabel, sawLabel, noiseLabel;
    Label oscName, oscVolumeLabel, modLabel, modSelectionLabel, modIndexLabel, modOffLabel, AMLabel, FMLabel;
    Label c_A_Label, c_D_Label, c_S_Label, c_R_Label, cNameLabel;
    Label m_A_Label, m_D_Label, m_S_Label, m_R_Label, mNameLabel;
    Label dropDownLabel;
    
    SineWave sine, mod; // sine osc
    BlitSaw saw; // sawtooth osc
    BlitSquare square;
    Random random;
    Smooth smooth[4];
    
    KeyPress key;
    ComboBox dropDown;
    
    double currentSampleRate, gain, oscFreq, modIndex;
    double c_A, c_D, c_S, c_R;
    double m_A, m_D, m_S, m_R;
    int oscSelection = 0, oscOnOff = 0;
    int presetNum = 0;
    
    void LoadPresets(int p) {
        if (p == 1) {
            oscKnob.setValue(0.0); oscSelection = oscKnob.getValue();
            modSelectionKnob.setValue(2.0);
            modKnob.setValue(oscFreq*1.4); mod.setFrequency(modKnob.getValue());
            modIndexKnob.setValue(800.0);
            modIndex = modIndexKnob.getValue();
            
            c_A_Knob.setValue(1.0); c_A = c_A_Knob.getValue();
            c_D_Knob.setValue(2000.0); c_D = c_D_Knob.getValue();
            c_S_Knob.setValue(0.0); c_S = c_S_Knob.getValue();
            c_R_Knob.setValue(1000.0); c_R = c_R_Knob.getValue();
            m_A_Knob.setValue(5.0); m_A = m_A_Knob.getValue();
            m_D_Knob.setValue(1.0); m_D = m_D_Knob.getValue();
            m_S_Knob.setValue(1.0); m_S = m_S_Knob.getValue();
            m_R_Knob.setValue(1.0); m_R = m_R_Knob.getValue();
            
            std::cout << modIndex;
        }
        if (p == 2) {
            oscKnob.setValue(0.0); oscSelection = oscKnob.getValue();
            modSelectionKnob.setValue(2.0);
            modKnob.setValue(oscFreq); mod.setFrequency(modKnob.getValue());
            modIndexKnob.setValue(1000.0);
            modIndex = modIndexKnob.getValue();
            
            c_A_Knob.setValue(50); c_A = c_A_Knob.getValue();
            c_D_Knob.setValue(200.0); c_D = c_D_Knob.getValue();
            c_S_Knob.setValue(0.45); c_S = c_S_Knob.getValue();
            c_R_Knob.setValue(400.0); c_R = c_R_Knob.getValue();
            m_A_Knob.setValue(150); m_A = m_A_Knob.getValue();
            m_D_Knob.setValue(200); m_D = m_D_Knob.getValue();
            m_S_Knob.setValue(0.85); m_S = m_S_Knob.getValue();
            m_R_Knob.setValue(200.0); m_R = m_R_Knob.getValue();
        }
        if (p == 3) {
            oscKnob.setValue(0.0); oscSelection = oscKnob.getValue();
            modSelectionKnob.setValue(2.0);
            modKnob.setValue(oscFreq*2/3); mod.setFrequency(modKnob.getValue());
            modIndexKnob.setValue(1500.0);
            modIndex = modIndexKnob.getValue();
            
            c_A_Knob.setValue(40); c_A = c_A_Knob.getValue();
            c_D_Knob.setValue(800.0); c_D = c_D_Knob.getValue();
            c_S_Knob.setValue(0.1); c_S = c_S_Knob.getValue();
            c_R_Knob.setValue(10.0); c_R = c_R_Knob.getValue();
            m_A_Knob.setValue(40); m_A = m_A_Knob.getValue();
            m_D_Knob.setValue(900); m_D = m_D_Knob.getValue();
            m_S_Knob.setValue(0); m_S = m_S_Knob.getValue();
            m_R_Knob.setValue(10); m_R = m_R_Knob.getValue();
        }
        if (p == 4) {
            oscKnob.setValue(0.0); oscSelection = oscKnob.getValue();
            modSelectionKnob.setValue(2.0);
            modKnob.setValue(3); mod.setFrequency(modKnob.getValue());
            modIndexKnob.setValue(650);
            modIndex = modIndexKnob.getValue();
            
            c_A_Knob.setValue(20); c_A = c_A_Knob.getValue();
            c_D_Knob.setValue(1.0); c_D = c_D_Knob.getValue();
            c_S_Knob.setValue(1.0); c_S = c_S_Knob.getValue();
            c_R_Knob.setValue(20.0); c_R = c_R_Knob.getValue();
            m_A_Knob.setValue(20); m_A = m_A_Knob.getValue();
            m_D_Knob.setValue(1); m_D = m_D_Knob.getValue();
            m_S_Knob.setValue(1.0); m_S = m_S_Knob.getValue();
            m_R_Knob.setValue(20); m_R = m_R_Knob.getValue();
        }
    }
    void UpdateModFreq(int p) {
        if (p == 1) {
            modKnob.setValue(oscFreq*1.4);
            mod.setFrequency(oscFreq*1.4);
        }
        else if (p == 2) {
            modKnob.setValue(oscFreq);
            mod.setFrequency(oscFreq);
        }
        else if (p == 3) {
            oscFreq *= 1.5;
            modKnob.setValue(oscFreq*2/3);
            mod.setFrequency(oscFreq*2/3);
        }
        else if (p == 4) {
            oscFreq *= 2;
            modKnob.setValue(3);
            mod.setFrequency(3);
        }
    }
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};

Component* createMainContentComponent()     { return new MainContentComponent(); }


#endif  // MAINCOMPONENT_H_INCLUDED
