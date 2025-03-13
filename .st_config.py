#!/usr/bin/env python3

import stlib.commands.shell
import stlib.commands.pb_decode
import stlib.shell

repoinfo = stlib.shell.repoinfo()

CONFIG = {
    'subpaths': {
        'rr':  ( 'repo root',   []),
    },
    'code_search_paths': {
        'davelib': {
            'root': {
                'default': True,
                'include': ['.' ],
            },
        },
    },
    'commands': {
    }
}

