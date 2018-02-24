/**
 *  Fireplace
 *
 *  Copyright 2018 Matthew Nichols
 *
 *  Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except
 *  in compliance with the License. You may obtain a copy of the License at:
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software distributed under the License is distributed
 *  on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License
 *  for the specific language governing permissions and limitations under the License.
 *
 */
metadata {
	definition (name: "Fireplace", namespace: "Fireplace", author: "Matthew Nichols") {
		capability "Switch"
	}
    
	simulator {
		// TODO: define status and reply messages here
	}

    tiles(scale: 2) {
        standardTile("switch", "device.switch", width: 2, height: 2, canChangeIcon: true) {
            state "off", label: 'Off', action: "switch.on",
                  icon: "st.Seasonal Winter.seasonal-winter-009", backgroundColor: "#ffffff", nextState: "on"
            state "on", label: 'On', action: "switch.off",
                  icon: "st.Seasonal Winter.seasonal-winter-009", backgroundColor: "#00a0dc", nextState: "off"
        }     
        main("switch")
    }
}

// parse events into attributes
def parse(String description) {
	log.debug "Parsing '${description}'"
}

// handle commands

def on() {
	log.debug "Executing 'on'"
    zigbee.smartShield(text: "on").format()
	//sendEvent(name: "switch", value: "on")   
}

def off() {
	log.debug "Executing 'off'"
    zigbee.smartShield(text: "off").format()
	//sendEvent(name: "switch", value: "off")   
}
