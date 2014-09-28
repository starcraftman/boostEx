#!/usr/bin/env python
# encoding: utf-8
import libBoost as bLib

def main():
    """ Main function. """
    print bLib.greet()

    planet = bLib.World("Hello there.")
    print planet.greet()
    planet.set("howdy")
    print planet.greet()

if __name__ == '__main__':
    main()

