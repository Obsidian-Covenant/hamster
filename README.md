# Hamster

## Modernization Covenant

This is a refactored and modernized edition of **hamster**, a tool to actively recover LEAP/PPTP passwords.

Key changes:

- ✅ Fixed errors and warnings caused by old libraries
- ✅ Updated Makefile and make process
- ✅ Refactored code to be used with latest gcc version

### Installation

#### Dependencies

Build dependencies:
```
gcc
```

Runtime dependencies:
```
libpcap
```

#### From source

```bash
git clone https://github.com/Obsidian-Covenant/hamster.git
cd hamster
make
sudo make install
cd ferret
make
sudo make install
```

## README

### Intro

Hamster is tool or "sidejacking". It acts as a proxy server that
replaces your cookies with session cookies stolen from somebody
else, allowing you to hijack their sessions.

Cookies are sniffed using the Ferret program. You need a copy of
that as well.

### Building

The projects/makefiles are in the "hamster" directory.

Building is pretty straightforward. If you want to make your own project, 
you can simply compile all the files together. Any errors that occur 
should be obvious how to fix.

### Changes

I'm currently rearranging how the code works, things might be in odd
places at the moment.

### See also

See https://hamster.erratasec.com for more information.

Robert Graham
March 9, 2009
