#include "Settings.h"

#include "parson/parson.h"

Settings& Settings::instance() {
    static Settings b;
    return b;
}

std::map<Killproof, bool> Settings::getActive() const {
    return active;
}

Settings::~Settings() {
    saveToFile();
}

Settings::Settings() {
	// set defaults, they will be overriden, with what is saved in the file
	// raid
	active[Killproof::li] = true;
	active[Killproof::ld] = true;
	// fractal
	active[Killproof::ufe] = true;
	active[Killproof::uce] = true;
	// w1
	active[Killproof::vg] = false;
	active[Killproof::gorse] = false;
	active[Killproof::sabetha] = false;
	// w2
	active[Killproof::sloth] = false;
	active[Killproof::matthias] = false;
	// w3
	active[Killproof::escort] = false;
	active[Killproof::kc] = false;
	active[Killproof::xera] = false;
	// w4
	active[Killproof::cairn] = false;
	active[Killproof::mo] = false;
	active[Killproof::samarog] = false;
	active[Killproof::deimos] = false;
	// w5
	active[Killproof::desmina] = false;
	active[Killproof::river] = false;
	active[Killproof::statues] = false;
	active[Killproof::dhuum] = true;
	// w6
	active[Killproof::ca] = false;
	active[Killproof::twins] = false;
	active[Killproof::qadim] = true;
	// w7
	active[Killproof::adina] = false;
	active[Killproof::sabir] = false;
	active[Killproof::qadim2] = true;
	
	// according to standard, this constructor is completely thread-safe
	// read settings from file
	readFromFile();
}

void Settings::saveToFile() {
    // setup json object
    JSON_Value* rootValue = json_value_init_object();
    JSON_Object* rootObject = json_value_get_object(rootValue);

    // write active map
    JSON_Value* activeValue = json_value_init_array();
    JSON_Array* activeArray = json_value_get_array(activeValue);
	
    for (auto activeVal : active) {
	    JSON_Value* activeSingleValue = json_value_init_object();
	    JSON_Object* activeSingleObject = json_value_get_object(activeSingleValue);

        json_object_set_number(activeSingleObject, "key", static_cast<double>(activeVal.first));
        json_object_set_boolean(activeSingleObject, "value", activeVal.second);

        json_array_append_value(activeArray, activeSingleValue);
	}

    json_object_set_value(rootObject, "active", activeValue);

    json_serialize_to_file_pretty(rootValue, "addons\\arcdps\\arcdps_killproof.me.json");
    
    json_value_free(rootValue);
}

void Settings::readFromFile() {
    JSON_Value* rootValue = json_parse_file("addons\\arcdps\\arcdps_killproof.me.json");
    if (json_value_get_type(rootValue) != JSONObject) {
        return;
    }
	
	JSON_Object* rootObject = json_value_get_object(rootValue);

    JSON_Array* activeArray = json_object_get_array(rootObject, "active");

    for (size_t i = 0; i < json_array_get_count(activeArray); ++i) {
        JSON_Object* activeObject = json_array_get_object(activeArray, i);

        double activeKey = json_object_get_number(activeObject, "key");
        bool activeValue = json_object_get_boolean(activeObject, "value");

        active[static_cast<Killproof>(activeKey)] = activeValue;
    }

    json_value_free(rootValue);
}
