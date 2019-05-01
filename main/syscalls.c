/*
* Copyright (c) 2019 Cristóvão Zuppardo Rufino
* See LICENCE file for more information
*/

void _exit(int status) { (void)status; while(1); }

int _close(int file) { return -1; }

int _isatty(int file) { return 1; }

int _open(const char *name, int flags, int mode) { return -1; }

int _write(int file, char *p, int len) { return -1; }

int _read(int file, char *p, int len) { return -1; }

char *_sbrk(int incr) { return 0; }

int _kill(int pid, int sig) { return -1; }

int _getpid(void) { return -1; }

int _fstat(void) { return -1; }

int _lseek(void) { return -1; }