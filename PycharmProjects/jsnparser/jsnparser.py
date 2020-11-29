# Простейшая проверка работы с json
# Выводим значение по имени ключа.
#
import json

result_file = "nodes_for_edit.lst"
#file = open('orange.json',mode='r')
file = open('result_juno.json',mode='r')
json_string = file.read()
# close the file
file.close()

# распарсенная строка
parsed_string = json.loads(json_string)
h_number=parsed_string['subtotal']
file = open(result_file,'w')
for i in range (h_number):
#    print(parsed_string['results'][i]['certname'])
    if parsed_string['results'][i]['configuration_status_label'] == "No reports":
        print(parsed_string['results'][i]['ip'])
        file.write(parsed_string['results'][i]['ip']+'\n')



#print(parsed_string['results'][1]['certname'])
#print(parsed_string['subtotal'])
#print(h_number)
#print(parsed_string['certname'])
#print(parsed_string['configuration_status_label'])
