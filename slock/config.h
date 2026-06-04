/* user and group to drop privileges to */
static const char *user  = "elytra";
static const char *group = "elytra";

static const char *colorname[NUMCOLS] = {
  [INIT] =   "#1a1b26",     /* after initialization (Tokyo Night Background) */
  [INPUT] =  "#7aa2f7",     /* during input (Tokyo Night Blue) */
  [FAILED] = "#f7768e",     /* wrong password (Tokyo Night Red) */
};

/* treat a cleared input like a wrong password (color) */
static const int failonclear = 1;
