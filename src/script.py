Finput = open("index.html", 'r')
Foutput = open("index.h", 'w')

Foutput.write('#include <Arduino.h>\n\n')

Foutput.write('\n\nString  index_html_0 =  "')

list_number = 0

example = Finput.read()
example = example.replace('"', '\\"')[:-1].replace('\n', '').replace('0/30', '";\nString  index_html_1 =  "')
while list_number < 30:
    example = example.replace('text'+str(list_number)+'\\">', 'text'+str(list_number)+'\\">";\nString list'+str(list_number)+' =  "')
    example = example.replace('id=\\"text'+str(list_number)+'\\">\\";', 'id=\\"text1\\">";')
    list_number += 1

Foutput.write(example)
Foutput.write('";')

Finput.close()
Foutput.close()