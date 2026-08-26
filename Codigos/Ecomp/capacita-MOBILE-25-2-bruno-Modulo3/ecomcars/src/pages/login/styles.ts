import Checkbox from "expo-checkbox";
import { Dimensions, StyleSheet, TextComponent } from "react-native";

export const styles = StyleSheet.create({
    container: {
        flexGrow: 1,
        justifyContent: 'center',
        alignItems: 'flex-start',
        paddingTop: 70,
        paddingHorizontal: 30,
    },   

    header: {
        width: '100%',
        justifyContent: 'center',
        alignItems: 'center',
    },

    input: {
        width: '100%',
        height: 40,
        borderWidth: 2,
        borderColor: '#A07A28',
        borderRadius: 20,
        marginBottom: 20,
        paddingLeft: 18,
        paddingTop: 10,
    },

    button: {
        width: '100%',
        height: 40,
        backgroundColor: '#A07A28',
        borderRadius: 20,
        justifyContent: 'center',
        alignItems: 'center',
        marginBottom: 80,
    },

    checkboxcontainer: {
        flexDirection: 'row',
        marginBottom: 20,
        marginTop: -10,
    },

    checkbox: {
        marginRight: 8,
    },

    titulo: {
        fontSize: 40,
        fontWeight: 100,
        marginBottom: 80,
    },

    subtitulo: {
        fontSize: 40,
        fontWeight: 100,
        marginBottom: 40,
        color: '#A07A28',
    },

    textoColorido: {
        color: '#A07A28',
        fontWeight: 500,
    },


    textoButton: {
        fontSize: 16,
        color: '#ffffff',
        fontWeight: 500,
    },

    checkboxText: {
        fontSize: 14,
        color: '#A07A28',
        fontWeight: 400,
    },
});
      