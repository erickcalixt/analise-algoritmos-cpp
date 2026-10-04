import os

# Cria uma pasta para não misturar com os seus códigos
pasta_testes = "casos_de_teste"
os.makedirs(pasta_testes, exist_ok=True)

# Tamanhos de 0 a 500.000, pulando de 25.000 em 25.000
tamanhos = list(range(0, 500001, 25000))

# Vamos assumir que "num" é o exercício 1. 
num_exercicio = 1

for val in tamanhos:
    # Segue a padronização: p<num>v<val>.txt
    nome_arquivo = f"p{num_exercicio}v{val}.txt"
    caminho_completo = os.path.join(pasta_testes, nome_arquivo)
    
    with open(caminho_completo, 'w') as f:
        # Pior caso: ordem decrescente (do maior para o menor)
        # Se val for 0, o ficheiro fica vazio, o que é correto
        if val > 0:
            # Cria a lista de strings e junta com quebras de linha
            numeros = [str(i) for i in range(val, 0, -1)]
            f.write('\n'.join(numeros))
            
    print(f"Ficheiro {nome_arquivo} gerado com sucesso!")

print("\nTodos os casos de teste do pior caso foram gerados na pasta 'casos_de_teste'.")