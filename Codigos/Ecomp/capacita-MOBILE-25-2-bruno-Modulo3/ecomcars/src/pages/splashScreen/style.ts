import { Dimensions, StyleSheet, TextComponent } from "react-native";

export const styles = StyleSheet.create({
    container: {
        width: Dimensions.get('window').width,
        height: Dimensions.get('window').height,
        justifyContent: 'center',
        alignItems: 'center',
    },

    text : {
        color: '#ffffff',
        fontSize: 50,
        fontWeight: 200,
    },

    textCars: {
        color: '#ffffffff',
        fontSize: 50,
        fontWeight: 400,
    },

    text2: {
        color: '#ffffff',
        fontSize: 15,
        marginTop: 10,
    }

});