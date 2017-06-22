#!/usr/bin/env python3

def resistor_divider(v, r1, r2):
    ''' 
        returns the output voltage for one input voltage and two resitors.
    '''
    rtot = r1 + r2
    return r2 / rtot * v

def non_inverting_opamp_gain(rf, r1):
    '''
    @param rf Resistor between output and inverting input.
    @param r1 Resistor between ground and inverting input.
    '''
    return 1.0 + rf/r1

def non_inverting_opamp(Vin, Rf, Rg):
    '''
    Returns the voltage out and gain of an ideal non-inverting opamp
    @param Vin, the input voltage to the non-inverting input
    @param Rf,  the value of the resistor in between output and inverting input
    @param Rg,  the value of the resistor between inverting input and ground.

    @returns a tuple of which the first member is vout and the second is gain
    '''
    gain = non_inverting_opamp_gain(Rf, Rg)
    vout = gain * Vin
    return vout, gain

