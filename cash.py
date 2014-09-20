# -*- coding: utf-8 -*-
"""
    cash.cash
    ~~~~~~~~~

    cache + hash = cash
    
    :copyright: (c) 2014 by Maverick Chan.
    :license: MIT License, see LICENSE for more details.
"""

def make_hash(key):
    """Makes hash by summing up string's ascii codes"""
    key = str(key)
    hash_ = 0
    for c in key:
        hash_ += ord(c)
    return hash_


class FalseValue(object):
    """
    This class is needed when users do this:
    >>> set('some_key', False)

    Since Cash uses None as indicator that the slot is unused,
    a new, dummy type needs to be made to replace the user's falsey
    value.

    When get('some_key') is performed, makes check if it's
    an instance of FalseValue.
    """
    def __init__(self, value):
        self.value = value


HASH_TABLE = []
def set(key, value):
    table = HASH_TABLE
    hash_ = make_hash(key)
    # Value is falsey, special procedure to handle
    if not value:
        value = FalseValue(value)
    try:
        table[hash_] = value
        return True
    except IndexError:
        diff = hash_ - len(table)
        table.extend([None] * (diff+1))
        table[hash_] = value
        return True


def set_multi(key_values):
    map(lambda x: set(x, key_values[x]), key_values)
    return True


def raise_key_error(key):
    raise KeyError("Key '{}' not present in hash table".format(key))


def get(key):
    table = HASH_TABLE
    hash_ = make_hash(key)
    try:
        value = table[hash_]
        if value:
            if isinstance(value, FalseValue):
                value = value.value
            return value
        else:
            return None
    except IndexError:
        return None


def get_multi(*keys):
    return map(get, keys)


def delete(key):
    table = HASH_TABLE
    hash_ = make_hash(key)
    try:
        if table[hash_]:
            table[hash_] = None
            return True
        else:
            raise_key_error(key)
    except IndexError:
        raise_key_error(key)

def delete_multi(*keys):
    map(delete, keys)
    return True
