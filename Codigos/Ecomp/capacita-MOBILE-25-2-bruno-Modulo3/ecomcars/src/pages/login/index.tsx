import React from "react";
import { Text, View, TextInput, TouchableOpacity, KeyboardAvoidingView, Platform, Alert } from 'react-native';
import { styles } from "./styles";
import Checkbox from "expo-checkbox";
import { StackScreenProps } from '@react-navigation/stack';

//definicao das telas que fazem parte da navegacao
export type rootStackParamList = {
    Login: undefined;
    Register: undefined;
    splashScreen: undefined;
    Tabs: undefined;
};

//propiedade para a navegacao de telas
type Props = StackScreenProps<rootStackParamList, 'Login'>;

//funcao da tela de login, possui ligaçao com a tela de registro
export default function Login({navigation}: Props) {
    const [email, setEmail] = React.useState('');
    const [password, setPassword] = React.useState('');
    const [isChecked, setChecked] = React.useState(false);

    //funcao que verifica se houve uma entrada "valida" no login
    //ainda nao verifica se o email e senha estao corretos, apenas se os campos foram preenchidos
    function getLogin() {
        try {
            if (!email || !password) {
                return Alert.alert('Erro', 'Por favor, preencha todos os campos.');
            }

            Alert.alert('Sucesso', 'Login realizado com sucesso!');
            navigation.navigate('Tabs');
        } catch (error) {
        console.log(error);
        };
    }

    return (
        <KeyboardAvoidingView behavior={Platform.OS === 'ios' ? 'padding' : 'height'} style={{ flex: 1 }}>
        <View style={styles.container}>
            <View style={styles.header}>
                <Text style={styles.titulo}>
                    ecom<Text style={styles.textoColorido}>Cars</Text><Text style={styles.subtitulo}>+</Text>
                </Text>
            </View>
        
            <View style={styles.header}>
                <Text style={styles.subtitulo}>
                    Entrar
                </Text>
            </View>

            <View style={styles.input}>
                <TextInput placeholder="E-mail"
                    value={email}
                    onChangeText={setEmail}>
                </TextInput>
            </View>

            <View style={styles.input}>
                    <TextInput placeholder="Senha"
                        value={password}
                        onChangeText={setPassword}
                        secureTextEntry={!isChecked}>
                    </TextInput>
            </View>

            <View style={styles.checkboxcontainer}>
                <Checkbox 
                    style={styles.checkbox} 
                    value={isChecked} 
                    onValueChange={setChecked}>
                </Checkbox>
                <Text style={styles.checkboxText}>Mostrar senha</Text>
            </View>

            <View style={styles.button}>
                <TouchableOpacity onPress={() => getLogin()}>
                    <Text style={styles.textoButton}>Entrar no ecomCars+</Text>
                </TouchableOpacity>
            </View>

            <View style={styles.button}>    
                <TouchableOpacity 
                onPress={() => navigation.navigate('Register')}>
                    <Text style={styles.textoButton}>Registrar-me</Text>
                </TouchableOpacity>
            </View>
        </View>
        </KeyboardAvoidingView>
  );
}