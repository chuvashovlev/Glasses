Finput = open("index.html", 'r')
Foutput = open("index.h", 'w')

Foutput.write('#include <Arduino.h>\n\n')
#Foutput.write()


Foutput.write("String list0, list1, list2, list3, list4, list5, list6, list7, list8, list9, list10, list11, list12, list13, list14, list15, list16, list17, list18, list19, list20, list21, list22, list23, list24, list25, list26, list27, list28, list29;")
Foutput.write("\nint page = 0;")

Foutput.write('\n\nString  index_html =  "')
for i in Finput:
    Foutput.write(i.replace('"', '\\"')[:-1].replace('0/30', '" + String(page) + "/30'))

Foutput.write('";')

Finput.close()
Foutput.close()