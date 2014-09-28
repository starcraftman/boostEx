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

    var = bLib.Var("Work")
    var.val = 10
    print var.val
    print var.name

    prop = bLib.ClassProp()
    prop.value = 3.14
    prop.value = prop.rovalue
    print prop.rovalue
    print prop.value
    try:
        prop.rovalue = 2.17
    except AttributeError:
        pass
    except Exception, exe:
        print exe.message

if __name__ == '__main__':
    main()

