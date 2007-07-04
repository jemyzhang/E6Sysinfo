#ifndef _PICTURE_H_
#define _PICTURE_H_
/* XPM */
static const char *Dot_xpm[] = {
/* width height num_colors chars_per_pixel */
"    10    10        8            1",
/* colors */
"` c #000000",
". c #949494",
"# c #444644",
"a c #d1cfd1",
"b c #353335",
"c c #777677",
"d c none",
"e c #e4e2e4",
/* pixels */
"ddd.bbcedd",
"da``````.d",
"d````````a",
"c````````b",
"#`````````",
"b`````````",
"c````````b",
"e````````.",
"d.``````#d",
"ddab``b.dd"
};

typedef struct QPoint_st {
    int x;
    int y;
};
static const QPoint_st static_screen_pos[] ={
//    static image positons
    {-225,-2},
};

static const char **static_screen_xpm[] = {
	Dot_xpm,
};
#endif

