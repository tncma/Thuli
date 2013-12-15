
package com.hackathon.cma.spark.parsers;

import com.fasterxml.jackson.databind.JsonNode;
import com.hackathon.cma.spark.models.Thuli;
import java.util.ArrayList;
import java.util.Iterator;

public class ThuliParser {

    public static ArrayList<Thuli> ParseThuligal(JsonNode nodes) {
        ArrayList<Thuli> thuligal = new ArrayList<Thuli>();
        Iterator<JsonNode> keys = nodes.elements();
        while (keys.hasNext()) {
            Thuli thuli = new Thuli();
            JsonNode node = keys.next();
            thuli.setUuid(node.path("uuid").asText());
            thuli.setSubject(node.path("title").asText());
            thuli.setBody(node.path("body").asText());
            thuli.setUsername(node.path("author_name").asText());
            thuli.setStatus(node.path("state").asText());
        }

        return thuligal;
    }
}
