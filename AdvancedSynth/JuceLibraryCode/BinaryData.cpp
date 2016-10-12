/* ==================================== JUCER_BINARY_RESOURCE ====================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

namespace BinaryData
{

//================== SKINI.msg ==================
static const unsigned char temp_binary_data_0[] =
"/*********************************************************/\n"
"/*\n"
"  Definition of SKINI Message Types and Special Symbols\n"
"     Synthesis toolKit Instrument Network Interface\n"
"\n"
"  These symbols should have the form:\n"
"\n"
"   \\c __SK_<name>_\n"
"\n"
"  where <name> is the string used in the SKINI stream.\n"
"\n"
"  by Perry R. Cook, 1995-2011.\n"
"*/\n"
"/*********************************************************/\n"
"\n"
"#ifndef __SKINI_MSG__\n"
"#define __SKINI_MSG__\n"
"\n"
"namespace stk {\n"
"\n"
"#define NOPE        -32767\n"
"#define YEP         1\n"
"#define SK_DBL      -32766\n"
"#define SK_INT      -32765\n"
"#define SK_STR      -32764\n"
"#define __SK_Exit_  999\n"
"\n"
"/***** MIDI COMPATIBLE MESSAGES *****/\n"
"/*** (Status bytes for channel=0) ***/\n"
"\n"
"#define __SK_NoteOff_                128\n"
"#define __SK_NoteOn_                 144\n"
"#define __SK_PolyPressure_           160\n"
"#define __SK_ControlChange_          176\n"
"#define __SK_ProgramChange_          192\n"
"#define __SK_AfterTouch_             208\n"
"#define __SK_ChannelPressure_        __SK_AfterTouch_\n"
"#define __SK_PitchWheel_             224\n"
"#define __SK_PitchBend_              __SK_PitchWheel_\n"
"#define __SK_PitchChange_            49\n"
"\n"
"#define __SK_Clock_                  248\n"
"#define __SK_SongStart_              250\n"
"#define __SK_Continue_               251\n"
"#define __SK_SongStop_               252\n"
"#define __SK_ActiveSensing_          254\n"
"#define __SK_SystemReset_            255\n"
"\n"
"#define __SK_Volume_                 7\n"
"#define __SK_ModWheel_               1\n"
"#define __SK_Modulation_             __SK_ModWheel_\n"
"#define __SK_Breath_                 2\n"
"#define __SK_FootControl_            4\n"
"#define __SK_Portamento_             65\n"
"#define __SK_Balance_                8\n"
"#define __SK_Pan_                    10\n"
"#define __SK_Sustain_                64\n"
"#define __SK_Damper_                 __SK_Sustain_\n"
"#define __SK_Expression_             11 \n"
"\n"
"#define __SK_AfterTouch_Cont_        128\n"
"#define __SK_ModFrequency_           __SK_Expression_\n"
"\n"
"#define __SK_ProphesyRibbon_         16\n"
"#define __SK_ProphesyWheelUp_        2\n"
"#define __SK_ProphesyWheelDown_      3\n"
"#define __SK_ProphesyPedal_          18\n"
"#define __SK_ProphesyKnob1_          21\n"
"#define __SK_ProphesyKnob2_          22\n"
"\n"
"/***  Instrument Family Specific ***/\n"
"\n"
"#define __SK_NoiseLevel_             __SK_FootControl_\n"
"\n"
"#define __SK_PickPosition_           __SK_FootControl_\n"
"#define __SK_StringDamping_          __SK_Expression_\n"
"#define __SK_StringDetune_           __SK_ModWheel_\n"
"#define __SK_BodySize_               __SK_Breath_\n"
"#define __SK_BowPressure_            __SK_Breath_\n"
"#define __SK_BowPosition_            __SK_PickPosition_\n"
"#define __SK_BowBeta_                __SK_BowPosition_\n"
"\n"
"#define __SK_ReedStiffness_          __SK_Breath_\n"
"#define __SK_ReedRestPos_            __SK_FootControl_\n"
"\n"
"#define __SK_FluteEmbouchure_        __SK_Breath_\n"
"#define __SK_JetDelay_               __SK_FluteEmbouchure_\n"
"\n"
"#define __SK_LipTension_             __SK_Breath_\n"
"#define __SK_SlideLength_            __SK_FootControl_\n"
"\n"
"#define __SK_StrikePosition_         __SK_PickPosition_\n"
"#define __SK_StickHardness_          __SK_Breath_\n"
"\n"
"#define __SK_TrillDepth_             1051\n"
"#define __SK_TrillSpeed_             1052\n"
"#define __SK_StrumSpeed_             __SK_TrillSpeed_\n"
"#define __SK_RollSpeed_              __SK_TrillSpeed_\n"
"\n"
"#define __SK_FilterQ_                __SK_Breath_\n"
"#define __SK_FilterFreq_             1062\n"
"#define __SK_FilterSweepRate_        __SK_FootControl_\n"
"\n"
"#define __SK_ShakerInst_             1071 \n"
"#define __SK_ShakerEnergy_           __SK_Breath_\n"
"#define __SK_ShakerDamping_          __SK_ModFrequency_\n"
"#define __SK_ShakerNumObjects_       __SK_FootControl_\n"
"\n"
"#define __SK_Strumming_              1090\n"
"#define __SK_NotStrumming_           1091\n"
"#define __SK_Trilling_               1092\n"
"#define __SK_NotTrilling_            1093\n"
"#define __SK_Rolling_                __SK_Strumming_\n"
"#define __SK_NotRolling_             __SK_NotStrumming_\n"
"\n"
"#define __SK_PlayerSkill_            2001\n"
"#define __SK_Chord_                  2002\n"
"#define __SK_ChordOff_               2003\n"
"\n"
"#define __SK_SINGER_FilePath_        3000\n"
"#define __SK_SINGER_Frequency_       3001\n"
"#define __SK_SINGER_NoteName_        3002\n"
"#define __SK_SINGER_Shape_           3003\n"
"#define __SK_SINGER_Glot_            3004\n"
"#define __SK_SINGER_VoicedUnVoiced_  3005\n"
"#define __SK_SINGER_Synthesize_      3006\n"
"#define __SK_SINGER_Silence_         3007\n"
"#define __SK_SINGER_VibratoAmt_      __SK_ModWheel_\n"
"#define __SK_SINGER_RndVibAmt_       3008\n"
"#define __SK_SINGER_VibFreq_         __SK_Expression_\n"
"\n"
"} // stk namespace\n"
"\n"
"#endif // __SKINI_MSG__";

const char* SKINI_msg = (const char*) temp_binary_data_0;


const char* getNamedResource (const char*, int&) throw();
const char* getNamedResource (const char* resourceNameUTF8, int& numBytes) throw()
{
    unsigned int hash = 0;
    if (resourceNameUTF8 != 0)
        while (*resourceNameUTF8 != 0)
            hash = 31 * hash + (unsigned int) *resourceNameUTF8++;

    switch (hash)
    {
        case 0x201a932e:  numBytes = 4532; return SKINI_msg;
        default: break;
    }

    numBytes = 0;
    return 0;
}

const char* namedResourceList[] =
{
    "SKINI_msg"
};

}
