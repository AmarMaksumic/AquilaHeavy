bool initialize_card(int card_pin);
String card_type();
String read_file(int card_pin, String file_name);
bool write_file(int card_pin, String file_name, String content);