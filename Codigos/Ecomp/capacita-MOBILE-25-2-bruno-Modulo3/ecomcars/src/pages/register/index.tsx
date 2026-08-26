import React from "react";
import { Text, View, TextInput, TouchableOpacity, KeyboardAvoidingView, Platform, Alert } from 'react-native';
import { styles } from "../login/styles";
import Checkbox from "expo-checkbox";
import { StackNavigationProp } from '@react-navigation/stack';
import { useNavigation } from '@react-navigation/native';
import { rootStackParamList } from "../login/index";

//funcao da tela de registro, possui ligaçao com a tela de login apos o registro
export default function Register() {
    const [email, setEmail] = React.useState('');
    const [password, setPassword] = React.useState('');
    const [isChecked, setChecked] = React.useState(false);
    const [nome, setNome] = React.useState('');

    const navigation = useNavigation<StackNavigationProp<rootStackParamList, 'Register'>>();

    //funcao que valida o formato do email, o email digitado deve ser do Gmail
    function validateEmail(email: string) {
        return email.includes('@gmail.com');
    }

    //funcao que valida o formato da senha
    function validatePassword(password: string) {
        return password.length >= 6;
    }

    //funcao que verifica se houve uma entrada "valida" no registro
    function getResgister() {
        try {
            if (!email || !password || !nome) {
                return Alert.alert('Erro', 'Por favor, preencha todos os campos.');
            }
            if (!validatePassword(password)) {
                return Alert.alert('Erro', 'A senha deve ter pelo menos 6 caracteres.');
            }
            if (!validateEmail(email)) {
                return Alert.alert('Erro', 'Por favor, seu email deve ser do serviço Gmail.');
            }

            Alert.alert('Sucesso', 'Registro realizado com sucesso...\nFaça o login!');
            navigation.navigate('Login');
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
                    Registrar
                </Text>
            </View>

            <View style={styles.input}>
                <TextInput placeholder="Nome"
                    value={nome}
                    onChangeText={setNome}>
                </TextInput>
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
                    onValueChange = {setChecked}>
                </Checkbox>
                <Text style={styles.checkboxText}>Mostrar senha</Text>
            </View>

            <View style={styles.button}>
                <TouchableOpacity onPress={() => getResgister()}>
                    <Text style={styles.textoButton}>Registrar no ecomCars+</Text>
                </TouchableOpacity>
            </View>

        </View>
        </KeyboardAvoidingView>
  );
}