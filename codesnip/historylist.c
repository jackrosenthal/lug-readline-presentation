HIST_ENTRY ** histlst = history_list();
for (int i = 1; *histlst; i++, histlst++)
    printf("%d %s\n", i, (*histlst)->line);
