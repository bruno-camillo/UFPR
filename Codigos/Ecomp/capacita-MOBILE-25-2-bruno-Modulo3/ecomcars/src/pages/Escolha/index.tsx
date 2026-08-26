import React, { useState } from "react";
import { Text, View, TextInput, StyleSheet, TouchableOpacity, Image, KeyboardAvoidingView, Platform, Alert, FlatList, ListRenderItem } from 'react-native';
import Checkbox from "expo-checkbox";
import { StackScreenProps } from '@react-navigation/stack';
import { MaterialIcons } from "@expo/vector-icons";
import {styles} from '../Home/styles';
import MaterialCommunityIcons from '@expo/vector-icons/MaterialCommunityIcons';
import { getBorderColorAsync } from "expo-navigation-bar";
 
type Car = {
    id: number;
    modelo: string;
    marca: string;
    titulo: string;
    imagens: string[];
    especificacoes: {
        categoria: string;
        motor: string;
        transmissao: string;
        combustivel: string;
    };
    diaria: number;
    descricao: string;
    colorhex: string;
    logo: string;
};

const data = [
        {
            "id": 1,
            "modelo": "4 Series Coupe",
            "marca": "BMW",
            "titulo": "Sinta-se no controle",
            "imagens": [
                "https://i.imgur.com/orKLBCq.png",
                "https://1.bp.blogspot.com/-Oww1y-f1Kas/XtaWRNQ1GmI/AAAAAAAAeHU/JjDXj80gFw4xpl_1mSrw1kSayT-v36sfwCLcBGAsYHQ/s1600/Novo-BMW-Serie-4-Coupe-2021%2B%252846%2529.jpg",
                "https://i.ytimg.com/vi/35ytxA4at54/maxresdefault.jpg"
            ],
            "especificacoes": {
                "categoria": "CPE",
                "motor": "3.0T",
                "transmissao": "AT9",
                "combustivel": "Gasolina"
            },
            "diaria": 253.98,
            "descricao": "O Série 4 foi criado quando a BMW separou os modelos de 2 portas (coupé e conversível) do Série 3 em uma série separada. O Série 4 está atualmente em sua segunda geração.",
            "colorhex": "#3393AE",
            "logo": "https://freepnglogo.com/images/all_img/1719812219bmw-logo-transparent-png.png"
        },
        {
            "id": 2,
            "modelo": "Compass Sport",
            "marca": "Jeep",
            "titulo": "Pronto para a aventura",
            "imagens": [
                "https://i.imgur.com/U0D6B05.png",
                "https://www.autoo.com.br/fotos/2021/4/960_720/jeep_compass_2022_1_05042021_47664_960_720.jpg",
                "https://p2.trrsf.com/image/fget/cf/940/0/images.terra.com/2021/03/31/jeep-compass-2021-80deg-anniversario-(1).jpg"
            ],
            "especificacoes": {
                "categoria": "SUV",
                "motor": "2.0T",
                "transmissao": "AT6",
                "combustivel": "Flex"
            },
            "diaria": 195.98,
            "descricao": "A faixa de valor do carro da Jeep varia de R$ 135,23 mil para o Compass Sport T270 2021/2022 a R$ 212,87 mil para o Compass Limeted TD350 4x4, conforme o site da marca.",
            "colorhex": "#A07A28",
            "logo": "https://freepnglogo.com/images/all_img/jeep-425c.png"
        },
        {
            "id": 3,
            "modelo": "Renegade",
            "marca": "Jeep",
            "titulo": "Seu Jeep para o dia a dia",
            "imagens": [
                "https://i.imgur.com/X7SpxB2.png",
                "https://motorshow.com.br/wp-content/uploads/sites/2/2020/12/05_renegade.jpg",
                "https://fotos.jornaldocarro.estadao.com.br/wp-content/uploads/2020/06/09083849/Jeep-Renegade-painel-1160x585.jpg"
            ],
            "especificacoes": {
                "categoria": "SUV",
                "motor": "2.0T",
                "transmissao": "AT6",
                "combustivel": "Flex"
            },
            "diaria": 144.98,
            "descricao": "Com faróis com iluminação em full LED de série. Também, o novo Jeep Renegade recebeu novos equipamentos e lanternas em LED, no caso a da sua versão Longitude Flex.",
            "colorhex": "#302E15",
            "logo": "https://freepnglogo.com/images/all_img/jeep-425c.png"
        },
        {
            "id": 4,
            "modelo": "Cronos HGT",
            "marca": "Fiat",
            "titulo": "O sedan completo da Fiat",
            "imagens": [
                "https://i.imgur.com/qzAEPgS.png",
                "https://garagem360.com.br/wp-content/uploads/2021/05/FiatCronos13MT2-1-scaled.jpeg",
                "https://fotos.jornaldocarro.estadao.com.br/wp-content/uploads/2020/06/18190453/Fiat-Cronos-interior-1160x585.jpg"
            ],
            "especificacoes": {
                "categoria": "SED",
                "motor": "1.8A",
                "transmissao": "AT6",
                "combustivel": "Flex"
            },
            "diaria": 90.98,
            "descricao": "O novo Cronos 2021 levou para o interior a nova identidade da marca. O Logo Script está no centro do volante e no Welcome Moving nas telas de inicialização do painel de instrumentos e da central multimídia.",
            "colorhex": "#838384",
            "logo": "https://freepnglogo.com/images/all_img/fiat-logo-04f0.png"
        },
        {
            "id": 5,
            "modelo": "Argo Drive",
            "marca": "Fiat",
            "titulo": "Você não dirige, você sente",
            "imagens": [
                "https://i.imgur.com/blJcenW.png",
                "https://argo.fiat.com.br/content/dam/fiat/products/358/a4n/0/2022/page/360/806/06.jpg.thumb.1280.1280.png",
                "https://1.bp.blogspot.com/-mSjPPbJSaaY/X1uFWQIW4lI/AAAAAAAAinQ/-h9cRRIElRofJFxRmJIkXpVxdccKkpG_ACLcBGAsYHQ/s2048/HGT18interior_3.jpg"
            ],
            "especificacoes": {
                "categoria": "HAT",
                "motor": "1.0A",
                "transmissao": "M5",
                "combustivel": "Flex"
            },
            "diaria": 79.98,
            "descricao": "Carro mais vendido do mês em maio, o Fiat Argo conseguiu o feito de liderar o mercado pela primeira vez desde que foi lançado. Ele emplacou 10.929 unidades no mês passado, segundo dados da Fenabrave.",
            "colorhex": "#9e0303",
            "logo": "https://freepnglogo.com/images/all_img/fiat-logo-04f0.png"
        },
        {
            "id": 6,
            "modelo": "Mobi",
            "marca": "Fiat",
            "titulo": "Mobilidade em Primeiro Lugar ",
            "imagens": [
                "https://i.imgur.com/IUOmQQS.png",
                "https://p2.trrsf.com/image/fget/cf/940/0/images.terra.com/2021/05/22/fiat-mobi.jpg",
                "https://cdn.autopapo.com.br/box/uploads/2020/10/19101110/interior-do-fiat-mobi_trekking_2021.jpeg"
            ],
            "especificacoes": {
                "categoria": "SUB",
                "motor": "1.0A",
                "transmissao": "M5",
                "combustivel": "Flex"
            },
            "diaria": 62.98,
            "descricao": "Com mais de 215 mil unidades vendidas, o Fiat Mobi é equipado com o motor Fire Evo Flex 1.0 de até 75 cv de potência a 6.250 rpm. O propulsor tem selo A no Inmetro.",
            "colorhex": "#821D1D",
            "logo": "https://freepnglogo.com/images/all_img/fiat-logo-04f0.png"
        },
        {
            "id": 7,
            "modelo": "Leaf",
            "marca": "Nissan",
            "titulo": "Seu primeiro sedan elétrico",
            "imagens": [
                "https://i.imgur.com/vYhBsD0.png",
                "https://www.nissan-cdn.net/content/dam/Nissan/br/20210720/retoques_leaf/home/1500x750%20-%20005_F_Nissan%20Leaf%20MY20%20PRATA%20(1).jpg.ximg.l_full_m.smart.jpg.ximg.l_full_m.smart.jpg",
                "https://fotos.jornaldocarro.estadao.com.br/wp-content/uploads/2020/06/15153847/Nissan-Leaf-interior-1160x585.jpg"
            ],
            "especificacoes": {
                "categoria": "SED",
                "motor": "110k",
                "transmissao": "AT1",
                "combustivel": "Elétrico"
            },
            "diaria": 211.98,
            "descricao": "O Nissan LEAF está equipado com alguns dos sistemas de assistência à direção mais avançados que existem; dessa forma, além de ser o carro pioneiro em eletrificação em massa, é o seu companheiro ideal para tornar todos os dias simplesmente incríveis.",
            "colorhex": "#093958",
            "logo": "https://freepnglogo.com/images/all_img/nissan-2462.png"
        },
        {
            "id": 8,
            "modelo": "AMG C 63",
            "marca": "Mercedes",
            "titulo": "Para todos os tipos de força",
            "imagens": [
                "https://carsguide-res.cloudinary.com/image/upload/f_auto,fl_lossy,q_auto,t_default/v1/editorial/vhs/Mercedes-amg-g63.png",
                "https://www2.mercedes-benz.com.br/passengercars/mercedes-benz-cars/models/g-class/suv-w463/amg/interior-design/_jcr_content/par/doubleimagecombinati_1050290476/par/doubleimageelement_1145425682/asset.MQ6.12.20190926161404.jpeg",
                "https://cdn.motor1.com/images/mgl/e9OoP/s1/2019-mercedes-amg-g63.jpg"
            ],
            "especificacoes": {
                "categoria": "SUV",
                "motor": "4.0T",
                "transmissao": "AT9",
                "combustivel": "Gasolina"
            },
            "diaria": 279.98,
            "descricao": "Ele tem 28 anos de mercado só na geração atual, sendo que a primeira surgiu em 1979. Teria sido um bom clássico brasileiro se tivesse sido feito aqui naquela época, mas agora quem procura por este utilitário 4×4 de estilo rústico e zero km, terá de pagar uma pequena fortuna para tê-lo na garagem.",
            "colorhex": "#353840",
            "logo": "https://freepnglogo.com/images/all_img/1719941357mercedes-car-logo.png"
        },
        {
            "id": 9,
            "modelo": "Kicks",
            "marca": "Nissan",
            "titulo": "Esportividade e Espaço",
            "imagens": [
                "https://production.autoforce.com/uploads/version/profile_image/5938/comprar-1-6-advance-cvt-pack-plus_d91d12cca7.png",
                "https://cdn.motor1.com/images/mgl/ER6wz/s3/nissan-kicks-exclusive-2022.jpg",
                "https://uploads.bemparana.com.br/upload/image/noticia/galeria/noticiaimagens_143655_img1_novo-nissan-kicks-sense-manual-16-1200x801.jpg"
            ],
            "especificacoes": {
                "categoria": "SUV",
                "motor": "1.6A",
                "transmissao": "CVT",
                "combustivel": "Flex"
            },
            "diaria": 122.98,
            "descricao": "Atualmente, o Kicks é o carro mais vendido pela Nissan no Brasil (e, provavelmente, o mais rentável), com 25.153 emplacamentos desde janeiro.",
            "colorhex": "#B80000",
            "logo": "https://freepnglogo.com/images/all_img/nissan-2462.png"
        },
        {
            "id": 10,
            "modelo": "Uno Mille",
            "marca": "Fiat",
            "titulo": "Falta só uma escada",
            "imagens": [
                "https://img2.icarros.com/dbimg/imgmodelo/2/269_4.png",
                "https://www.grupoapj.com.br/novos/fotos_novos/uno_furgao2011/uno_furgao-FEFEFE.png",
                "https://www.autossegredos.com.br/wp-content/uploads/2018/11/fiat-mille-way-5.jpg"
            ],
            "especificacoes": {
                "categoria": "HAT",
                "motor": "1.0A",
                "transmissao": "M5",
                "combustivel": "Flex"
            },
            "diaria": 39.98,
            "descricao": "Por volta das 8h10, o homem e um comparsa entraram no mercado Epa e levaram duas peças de carne de lagarto. Pouco depois, as 8h49, o suspeito entrou sozinho no supermercado Dia e roubou 35 quilos de contra filé avaliados em R$ 1385,04. Ele fugiu em um Fiat Uno Mille verde.",
            "colorhex": "#7D7574",
            "logo": "https://freepnglogo.com/images/all_img/fiat-logo-04f0.png"
        }
    ]

type Marcas = {
    id: number;
    marca: string;
    logo: string | null;
};

const dataMarcas = [
    {
        "id": 0,
        "marca": "Todos",
        "logo": null,
    },
    {
        "id": 1,
        "marca": "BMW",
        "logo": "https://freepnglogo.com/images/all_img/1719812219bmw-logo-transparent-png.png",
    },
    {
        "id": 2,
        "marca": "Jeep",
        "logo": "https://freepnglogo.com/images/all_img/jeep-425c.png" ,
    },
    {
        "id": 3,
        "marca": "Fiat",
        "logo": "https://freepnglogo.com/images/all_img/fiat-logo-04f0.png",
    },
    {
        "id": 4,
        "marca": "Nissan",
        "logo": "https://freepnglogo.com/images/all_img/nissan-2462.png",
    },
    {
        "id": 5,
        "marca": "Mercedes",
        "logo": "https://freepnglogo.com/images/all_img/1719941357mercedes-car-logo.png",
    }
];

export default function Cars() {

    const [filtro, setFiltro] = useState('Todos');

    const handlePress = (marca: string) => {
        setFiltro(marca);
    };

    const renderMarcas: ListRenderItem<Marcas> = ({item, index}) => (
        <View style={[styles.marcas, {borderWidth: filtro === item.marca ? 3 : 0, borderColor: '#A07A28'}]}>
            <TouchableOpacity onPress={() => handlePress(item.marca)}>
                {item.logo ? (<Image
                    style={styles.marcasimage}
                    source={{uri: item.logo}}
                />) : (<Text style={styles.textMarcaTodos}>Todas</Text>)}
            </TouchableOpacity>
        </View>
    );

    const renderCars: ListRenderItem<Car> = ({item}) => (
        <View style={styles.flatlist2}>
                <View style={styles.cars}>
                    <Image
                        style={styles.flatlistimage2}
                        source={{uri : item.imagens[0]}}
                    />
                    <View style={{margin: 20}}>
                        <Text style={styles.textMarcaModelo}>{item.marca}</Text>
                        <Text style={styles.textMarcaModelo}>{item.modelo}</Text>
                    </View>
                </View>
                <View style={styles.informacoes}>
                    <View style={styles.especificacoes}>
                        <MaterialIcons name="directions-car" size={15} color={'#A07A28'}/>
                        <Text style={styles.textEspecificacoes}>{item.especificacoes.categoria}</Text>
                        <Text> </Text>
                        <MaterialCommunityIcons name="engine-outline" size={15} color='#A07A28' />
                        <Text style={styles.textEspecificacoes}>{item.especificacoes.motor}</Text>
                        <Text> </Text>
                        <MaterialCommunityIcons name="car-shift-pattern" size={15} color='#A07A28' />
                        <Text style={styles.textEspecificacoes}>{item.especificacoes.transmissao}</Text>
                    </View>

                    <Text style={styles.textPreco}>R${item.diaria}<Text style={{fontWeight:'300'}}>/dia</Text></Text>
                    
                    <TouchableOpacity style={styles.buttonCar2}>
                        <MaterialIcons 
                            name="arrow-right-alt"
                            size={30}
                            color='#A07A28' 
                            style={{alignSelf: 'center'}} />
                    </TouchableOpacity>
                </View>
            </View>
    );

    const carrosFiltrados = filtro === 'Todos'
    ? data
    : data.filter(item => item.marca === filtro);

    return (
        <View style={styles.container}>
            <View style={styles.header}>
                <Text style={styles.textTitulo}>
                    ecom<Text style={styles.textColorido}>Cars</Text><Text style={styles.simbolo}>+</Text>
                </Text>
            </View>

            <View style={styles.subtitulo}>
                <Text style={styles.textSubtitulo}>
                    <Text style={styles.negrito}>Compare</Text> e escolha
                </Text>
            </View>

            <View>
                <Text style={[styles.negrito, styles.topico]}>
                    Marcas
                </Text>
                <FlatList
                    data={dataMarcas}
                    renderItem={renderMarcas}
                    keyExtractor={item => item.id.toString()}
                    horizontal={true}
                />
            </View>

            <View>
                <Text style={[styles.negrito, styles.topico]}>
                    Carros
                </Text>
            </View>

            <View style={styles.flatlistcontainer}>
                <FlatList
                data={carrosFiltrados}
                renderItem={renderCars}
                keyExtractor={item => item.id.toString()}
                contentContainerStyle={{ paddingBottom: 300 }}
                />
            </View>
        </View>
    );
}

