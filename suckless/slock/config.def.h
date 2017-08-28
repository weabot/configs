/* user and group to drop privileges to */
static const char *user  = "nobody";
static const char *group = "nogroup";

static const char *colorname[NUMCOLS] = {
	[INIT] =   "#3F3F3F",     /* after initialization */
	[INPUT] =  "#80D4AA",   /* during input */
	[FAILED] = "#BC6C4C",   /* wrong password */
};

/* treat a cleared input like a wrong password (color) */
static const int failonclear = 1;
