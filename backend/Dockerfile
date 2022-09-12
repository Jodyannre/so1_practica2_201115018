FROM golang:alpine

WORKDIR /backend

COPY . .
RUN go mod download

RUN go build -o /exec

EXPOSE 4000

CMD ["/exec"]