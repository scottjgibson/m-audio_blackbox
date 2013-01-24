from struct import *
from collections import namedtuple


preset = namedtuple('preset', 'Header, Amp, Drive, Bass, Treble, Effect, FX_Speed_Freq, FX_Depth_Key, FX_Wet_Dry, \
                    Delay_time, Delay_Repeats, Delay_Volume, Drums_Send_To_FX, Preset_Volume, \
                    Exp_Pedal_Assign, Tempo, AmpFxDelRevOn, Mid, Linked_Drumbeat, Unused1, \
                    Compressor, Reverb_Volume, Reverb_Time, Reverb_High_Freq, Unused2, \
		    Name, Unused3')


preset_file = open('BASMAN.mwp2', 'rb')
preset_data = preset_file.read(76)
preset._make(unpack('<8sBBBBBBBBBBBBBBBBBBBBBBB9s6s30s', preset_data))
Header, Amp, Drive, Bass, Treble, Effect, FX_Speed_Freq, FX_Depth_Key, FX_Wet_Dry, \
                    Delay_time, Delay_Repeats, Delay_Volume, Drums_Send_To_FX, Preset_Volume, \
                    Exp_Pedal_Assign, Tempo, AmpFxDelRevOn, Mid, Linked_Drumbeat, Unused1, \
                    Compressor, Reverb_Volume, Reverb_Time, Reverb_High_Freq, Unused2, \
		    Name, Unused3 = unpack('<8sBBBBBBBBBBBBBBBBBBBBBBB9s6s30s', preset_data)
import pdb; pdb.set_trace()

